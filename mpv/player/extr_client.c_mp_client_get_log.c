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
struct mpv_handle {struct mp_log* log; } ;
struct mp_log {int dummy; } ;

/* Variables and functions */

struct mp_log *mp_client_get_log(struct mpv_handle *ctx)
{
    return ctx->log;
}