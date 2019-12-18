#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  obqueue; int /*<<< orphan*/  ibqueue; } ;
typedef  TYPE_1__ QMKUSBDriver ;

/* Variables and functions */
 int /*<<< orphan*/  CHN_CONNECTED ; 
 int /*<<< orphan*/  bqResumeX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chnAddFlagsI (TYPE_1__*,int /*<<< orphan*/ ) ; 

void qmkusbWakeupHookI(QMKUSBDriver *qmkusbp) {
    chnAddFlagsI(qmkusbp, CHN_CONNECTED);
    bqResumeX(&qmkusbp->ibqueue);
    bqResumeX(&qmkusbp->obqueue);
}