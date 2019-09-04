#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mp_log {int dummy; } ;
struct TYPE_3__ {int thread_count; } ;
typedef  TYPE_1__ AVCodecContext ;

/* Variables and functions */
 int MPMIN (int,int) ; 
 int av_cpu_count () ; 
 int /*<<< orphan*/  mp_verbose (struct mp_log*,char*,int) ; 
 int /*<<< orphan*/  mp_warn (struct mp_log*,char*) ; 

void mp_set_avcodec_threads(struct mp_log *l, AVCodecContext *avctx, int threads)
{
    if (threads == 0) {
        threads = av_cpu_count();
        if (threads < 1) {
            mp_warn(l, "Could not determine thread count to use, defaulting to 1.\n");
            threads = 1;
        } else {
            mp_verbose(l, "Detected %d logical cores.\n", threads);
            if (threads > 1)
                threads += 1; // extra thread for better load balancing
        }
        // Apparently some libavcodec versions have or had trouble with more
        // than 16 threads, and/or print a warning when using > 16.
        threads = MPMIN(threads, 16);
    }
    mp_verbose(l, "Requesting %d threads for decoding.\n", threads);
    avctx->thread_count = threads;
}