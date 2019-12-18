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
typedef  int /*<<< orphan*/  dacsample_t ;
typedef  int /*<<< orphan*/  DACDriver ;

/* Variables and functions */
 int /*<<< orphan*/ * dac_buffer ; 
 size_t nx ; 
 size_t ny ; 
 int nz ; 

__attribute__((used)) static void end_cb1(DACDriver *dacp, dacsample_t *buffer, size_t n) {
    (void)dacp;

    nz++;
    if (dac_buffer == buffer) {
        nx += n;
    } else {
        ny += n;
    }

    if ((nz % 1000) == 0) {
        // palTogglePad(GPIOD, GPIOD_LED3);
    }
}