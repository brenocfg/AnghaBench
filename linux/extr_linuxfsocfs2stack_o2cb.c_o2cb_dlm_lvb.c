#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ lvb; } ;
struct ocfs2_dlm_lksb {TYPE_1__ lksb_o2dlm; } ;

/* Variables and functions */

__attribute__((used)) static void *o2cb_dlm_lvb(struct ocfs2_dlm_lksb *lksb)
{
	return (void *)(lksb->lksb_o2dlm.lvb);
}