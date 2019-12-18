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
typedef  int /*<<< orphan*/  expchannel_t ;
typedef  int /*<<< orphan*/  EXTDriver ;

/* Variables and functions */
 int /*<<< orphan*/  EXTD1 ; 
 int /*<<< orphan*/  GPIOA ; 
 int /*<<< orphan*/  GPIOB ; 
 int /*<<< orphan*/  chSysLockFromISR () ; 
 int /*<<< orphan*/  chSysUnlockFromISR () ; 
 int /*<<< orphan*/  extChannelDisable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  extChannelEnable (int /*<<< orphan*/ *,int) ; 
 void* palReadPort (int /*<<< orphan*/ ) ; 
 void* porta_buffer ; 
 void* portb_buffer ; 

__attribute__((used)) static void extcb1(EXTDriver *extp, expchannel_t channel) {

    (void)extp;
    (void)channel;
    chSysLockFromISR();
    porta_buffer = palReadPort(GPIOA);
    portb_buffer = palReadPort(GPIOB);
    //Disable further interrupts that might occur on same button press.
    extChannelDisable(&EXTD1,0);
    extChannelDisable(&EXTD1,1);
    extChannelDisable(&EXTD1,2);
    extChannelDisable(&EXTD1,9);
    extChannelDisable(&EXTD1,10);
    extChannelDisable(&EXTD1,12);
    extChannelDisable(&EXTD1,13);
    extChannelDisable(&EXTD1,14);
    extChannelDisable(&EXTD1,15);

    extChannelEnable(&EXTD1,0);
    extChannelEnable(&EXTD1,1);
    extChannelEnable(&EXTD1,2);
    extChannelEnable(&EXTD1,9);
    extChannelEnable(&EXTD1,10);
    extChannelEnable(&EXTD1,12);
    extChannelEnable(&EXTD1,13);
    extChannelEnable(&EXTD1,14);
    extChannelEnable(&EXTD1,15);
    chSysUnlockFromISR();
}