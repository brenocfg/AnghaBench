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
typedef  int /*<<< orphan*/  mpv_handle ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (int /*<<< orphan*/ *,char*) ; 

void mpv_suspend(mpv_handle *ctx)
{
    MP_ERR(ctx, "mpv_suspend() is deprecated and does nothing.\n");
}