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
struct mgsl_struct {int loopmode_send_done_requested; int /*<<< orphan*/  cmr_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT13 ; 
 int /*<<< orphan*/  CMR ; 
 int /*<<< orphan*/  usc_OutReg (struct mgsl_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usc_loopmode_send_done( struct mgsl_struct * info )
{
 	info->loopmode_send_done_requested = false;
 	/* clear CMR:13 to 0 to start echoing RxData to TxData */
 	info->cmr_value &= ~BIT13;
 	usc_OutReg(info, CMR, info->cmr_value);
}