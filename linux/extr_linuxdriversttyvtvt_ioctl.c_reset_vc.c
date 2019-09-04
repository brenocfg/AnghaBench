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
struct TYPE_2__ {scalar_t__ frsig; scalar_t__ acqsig; scalar_t__ relsig; scalar_t__ waitv; int /*<<< orphan*/  mode; } ;
struct vc_data {int vt_newvt; int /*<<< orphan*/ * vt_pid; TYPE_1__ vt_mode; int /*<<< orphan*/  vc_num; int /*<<< orphan*/  vc_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  KD_TEXT ; 
 int /*<<< orphan*/  VT_AUTO ; 
 int /*<<< orphan*/  in_interrupt () ; 
 int /*<<< orphan*/  put_pid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_palette (struct vc_data*) ; 
 int /*<<< orphan*/  vt_reset_unicode (int /*<<< orphan*/ ) ; 

void reset_vc(struct vc_data *vc)
{
	vc->vc_mode = KD_TEXT;
	vt_reset_unicode(vc->vc_num);
	vc->vt_mode.mode = VT_AUTO;
	vc->vt_mode.waitv = 0;
	vc->vt_mode.relsig = 0;
	vc->vt_mode.acqsig = 0;
	vc->vt_mode.frsig = 0;
	put_pid(vc->vt_pid);
	vc->vt_pid = NULL;
	vc->vt_newvt = -1;
	if (!in_interrupt())    /* Via keyboard.c:SAK() - akpm */
		reset_palette(vc);
}