#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vo_vsync_info {void* last_queue_display_time; void* vsync_duration; scalar_t__ skipped_vsyncs; } ;
struct ra_swapchain {struct priv* priv; } ;
struct priv {unsigned int last_sync_refresh_count; unsigned int last_sync_qpc_time; unsigned int vsync_duration_qpc; int last_submit_qpc; int /*<<< orphan*/  swapchain; TYPE_1__* opts; } ;
typedef  int int64_t ;
typedef  unsigned int UINT ;
struct TYPE_6__ {unsigned int QuadPart; } ;
struct TYPE_7__ {unsigned int SyncRefreshCount; unsigned int PresentCount; unsigned int PresentRefreshCount; TYPE_2__ SyncQPCTime; } ;
struct TYPE_5__ {int sync_interval; } ;
typedef  scalar_t__ HRESULT ;
typedef  TYPE_3__ DXGI_FRAME_STATISTICS ;

/* Variables and functions */
 scalar_t__ DXGI_ERROR_FRAME_STATISTICS_DISJOINT ; 
 scalar_t__ FAILED (scalar_t__) ; 
 scalar_t__ IDXGISwapChain_GetFrameStatistics (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ IDXGISwapChain_GetLastPresentCount (int /*<<< orphan*/ ,unsigned int*) ; 
 void* mp_time_us () ; 
 void* qpc_to_us (struct ra_swapchain*,int) ; 
 void* qpc_us_now (struct ra_swapchain*) ; 

__attribute__((used)) static void d3d11_get_vsync(struct ra_swapchain *sw, struct vo_vsync_info *info)
{
    struct priv *p = sw->priv;
    HRESULT hr;

    // The calculations below are only valid if mpv presents on every vsync
    if (p->opts->sync_interval != 1)
        return;

    // GetLastPresentCount returns a sequential ID for the frame submitted by
    // the last call to IDXGISwapChain::Present()
    UINT submit_count;
    hr = IDXGISwapChain_GetLastPresentCount(p->swapchain, &submit_count);
    if (FAILED(hr))
        return;

    // GetFrameStatistics returns two pairs. The first is (PresentCount,
    // PresentRefreshCount) which relates a present ID (on the same timeline as
    // GetLastPresentCount) to the physical vsync it was displayed on. The
    // second is (SyncRefreshCount, SyncQPCTime), which relates a physical vsync
    // to a timestamp on the same clock as QueryPerformanceCounter.
    DXGI_FRAME_STATISTICS stats;
    hr = IDXGISwapChain_GetFrameStatistics(p->swapchain, &stats);
    if (hr == DXGI_ERROR_FRAME_STATISTICS_DISJOINT) {
        p->last_sync_refresh_count = 0;
        p->last_sync_qpc_time = 0;
    }
    if (FAILED(hr))
        return;

    // Detecting skipped vsyncs is possible but not supported yet
    info->skipped_vsyncs = 0;

    // Get the number of physical vsyncs that have passed since the last call.
    // Check for 0 here, since sometimes GetFrameStatistics returns S_OK but
    // with 0s in some (all?) members of DXGI_FRAME_STATISTICS.
    unsigned src_passed = 0;
    if (stats.SyncRefreshCount && p->last_sync_refresh_count)
        src_passed = stats.SyncRefreshCount - p->last_sync_refresh_count;
    p->last_sync_refresh_count = stats.SyncRefreshCount;

    // Get the elapsed time passed between the above vsyncs
    unsigned sqt_passed = 0;
    if (stats.SyncQPCTime.QuadPart && p->last_sync_qpc_time)
        sqt_passed = stats.SyncQPCTime.QuadPart - p->last_sync_qpc_time;
    p->last_sync_qpc_time = stats.SyncQPCTime.QuadPart;

    // If any vsyncs have passed, estimate the physical frame rate
    if (src_passed && sqt_passed)
        p->vsync_duration_qpc = sqt_passed / src_passed;
    if (p->vsync_duration_qpc)
        info->vsync_duration = qpc_to_us(sw, p->vsync_duration_qpc);

    // If the physical frame rate is known and the other members of
    // DXGI_FRAME_STATISTICS are non-0, estimate the timing of the next frame
    if (p->vsync_duration_qpc && stats.PresentCount &&
        stats.PresentRefreshCount && stats.SyncRefreshCount &&
        stats.SyncQPCTime.QuadPart)
    {
        // PresentRefreshCount and SyncRefreshCount might refer to different
        // frames (this can definitely occur in bitblt-mode.) Assuming mpv
        // presents on every frame, guess the present count that relates to
        // SyncRefreshCount.
        unsigned expected_sync_pc = stats.PresentCount +
            (stats.SyncRefreshCount - stats.PresentRefreshCount);

        // Now guess the timestamp of the last submitted frame based on the
        // timestamp of the frame at SyncRefreshCount and the frame rate
        int queued_frames = submit_count - expected_sync_pc;
        int64_t last_queue_display_time_qpc = stats.SyncQPCTime.QuadPart +
            queued_frames * p->vsync_duration_qpc;

        // Only set the estimated display time if it's after the last submission
        // time. It could be before if mpv skips a lot of frames.
        if (last_queue_display_time_qpc >= p->last_submit_qpc) {
            info->last_queue_display_time = mp_time_us() +
                (qpc_to_us(sw, last_queue_display_time_qpc) - qpc_us_now(sw));
        }
    }
}