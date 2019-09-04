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
typedef  int u16 ;
struct l2cap_ctrl {int reqseq; int final; int poll; int super; int sar; int txseq; scalar_t__ sframe; } ;

/* Variables and functions */
 int L2CAP_CTRL_FINAL_SHIFT ; 
 int L2CAP_CTRL_FRAME_TYPE ; 
 int L2CAP_CTRL_POLL_SHIFT ; 
 int L2CAP_CTRL_REQSEQ_SHIFT ; 
 int L2CAP_CTRL_SAR_SHIFT ; 
 int L2CAP_CTRL_SUPER_SHIFT ; 
 int L2CAP_CTRL_TXSEQ_SHIFT ; 

__attribute__((used)) static u16 __pack_enhanced_control(struct l2cap_ctrl *control)
{
	u16 packed;

	packed = control->reqseq << L2CAP_CTRL_REQSEQ_SHIFT;
	packed |= control->final << L2CAP_CTRL_FINAL_SHIFT;

	if (control->sframe) {
		packed |= control->poll << L2CAP_CTRL_POLL_SHIFT;
		packed |= control->super << L2CAP_CTRL_SUPER_SHIFT;
		packed |= L2CAP_CTRL_FRAME_TYPE;
	} else {
		packed |= control->sar << L2CAP_CTRL_SAR_SHIFT;
		packed |= control->txseq << L2CAP_CTRL_TXSEQ_SHIFT;
	}

	return packed;
}