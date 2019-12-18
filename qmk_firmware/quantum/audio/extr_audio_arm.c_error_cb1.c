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
typedef  int /*<<< orphan*/  dacerror_t ;
typedef  int /*<<< orphan*/  DACDriver ;

/* Variables and functions */
 int /*<<< orphan*/  chSysHalt (char*) ; 

__attribute__((used)) static void error_cb1(DACDriver *dacp, dacerror_t err) {
    (void)dacp;
    (void)err;

    chSysHalt("DAC failure");
}