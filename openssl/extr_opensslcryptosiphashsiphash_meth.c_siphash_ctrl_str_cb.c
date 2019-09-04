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

/* Variables and functions */
 int siphash_ctrl_int (void*,int,void*,size_t) ; 

__attribute__((used)) static int siphash_ctrl_str_cb(void *ctx, int cmd, void *buf, size_t buflen)
{
    return siphash_ctrl_int(ctx, cmd, buf, buflen);
}