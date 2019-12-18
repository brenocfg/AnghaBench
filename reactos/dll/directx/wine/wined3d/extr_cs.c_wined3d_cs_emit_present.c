#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int backbuffer_count; } ;
struct wined3d_swapchain {TYPE_3__** back_buffers; TYPE_2__ desc; TYPE_1__* front_buffer; } ;
struct wined3d_cs_present {void* flags; void* swap_interval; int /*<<< orphan*/  dst_rect; int /*<<< orphan*/  src_rect; struct wined3d_swapchain* swapchain; int /*<<< orphan*/  dst_window_override; int /*<<< orphan*/  opcode; } ;
struct wined3d_cs {int /*<<< orphan*/  pending_presents; TYPE_4__* ops; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* submit ) (struct wined3d_cs*,int /*<<< orphan*/ ) ;struct wined3d_cs_present* (* require_space ) (struct wined3d_cs*,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  resource; } ;
struct TYPE_5__ {int /*<<< orphan*/  resource; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  HWND ;
typedef  void* DWORD ;

/* Variables and functions */
 int InterlockedCompareExchange (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int InterlockedIncrement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WINED3D_CS_OP_PRESENT ; 
 int /*<<< orphan*/  WINED3D_CS_QUEUE_DEFAULT ; 
 struct wined3d_cs_present* stub1 (struct wined3d_cs*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct wined3d_cs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_pause () ; 
 int /*<<< orphan*/  wined3d_resource_acquire (int /*<<< orphan*/ *) ; 

void wined3d_cs_emit_present(struct wined3d_cs *cs, struct wined3d_swapchain *swapchain,
        const RECT *src_rect, const RECT *dst_rect, HWND dst_window_override,
        DWORD swap_interval, DWORD flags)
{
    struct wined3d_cs_present *op;
    unsigned int i;
    LONG pending;

    op = cs->ops->require_space(cs, sizeof(*op), WINED3D_CS_QUEUE_DEFAULT);
    op->opcode = WINED3D_CS_OP_PRESENT;
    op->dst_window_override = dst_window_override;
    op->swapchain = swapchain;
    op->src_rect = *src_rect;
    op->dst_rect = *dst_rect;
    op->swap_interval = swap_interval;
    op->flags = flags;

    pending = InterlockedIncrement(&cs->pending_presents);

    wined3d_resource_acquire(&swapchain->front_buffer->resource);
    for (i = 0; i < swapchain->desc.backbuffer_count; ++i)
    {
        wined3d_resource_acquire(&swapchain->back_buffers[i]->resource);
    }

    cs->ops->submit(cs, WINED3D_CS_QUEUE_DEFAULT);

    /* Limit input latency by limiting the number of presents that we can get
     * ahead of the worker thread. We have a constant limit here, but
     * IDXGIDevice1 allows tuning this. */
    while (pending > 1)
    {
        wined3d_pause();
        pending = InterlockedCompareExchange(&cs->pending_presents, 0, 0);
    }
}