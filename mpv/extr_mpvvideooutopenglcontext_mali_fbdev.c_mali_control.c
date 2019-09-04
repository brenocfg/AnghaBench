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
struct ra_ctx {int dummy; } ;

/* Variables and functions */
 int VO_NOTIMPL ; 

__attribute__((used)) static int mali_control(struct ra_ctx *ctx, int *events, int request, void *arg)
{
    return VO_NOTIMPL;
}