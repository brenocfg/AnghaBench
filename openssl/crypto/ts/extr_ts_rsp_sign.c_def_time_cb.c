#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct timeval {long tv_sec; long tv_usec; } ;
struct TS_resp_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TS_F_DEF_TIME_CB ; 
 int /*<<< orphan*/  TS_INFO_TIME_NOT_AVAILABLE ; 
 int /*<<< orphan*/  TS_RESP_CTX_add_failure_info (struct TS_resp_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TS_RESP_CTX_set_status_info (struct TS_resp_ctx*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TS_R_TIME_SYSCALL_ERROR ; 
 int /*<<< orphan*/  TS_STATUS_REJECTION ; 
 int /*<<< orphan*/  TSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int def_time_cb(struct TS_resp_ctx *ctx, void *data,
                       long *sec, long *usec)
{
    struct timeval tv;
    if (gettimeofday(&tv, NULL) != 0) {
        TSerr(TS_F_DEF_TIME_CB, TS_R_TIME_SYSCALL_ERROR);
        TS_RESP_CTX_set_status_info(ctx, TS_STATUS_REJECTION,
                                    "Time is not available.");
        TS_RESP_CTX_add_failure_info(ctx, TS_INFO_TIME_NOT_AVAILABLE);
        return 0;
    }
    *sec = tv.tv_sec;
    *usec = tv.tv_usec;

    return 1;
}