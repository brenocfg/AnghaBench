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
typedef  int UCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  I2CTransmitWord (int,int) ; 

__attribute__((used)) static void
I2cSetFrontpanelLed(UCHAR b)
{
  I2CTransmitWord( 0x10, 0x800 | b);  // sequencing thanks to Jarin the Penguin!
  I2CTransmitWord( 0x10, 0x701);
}