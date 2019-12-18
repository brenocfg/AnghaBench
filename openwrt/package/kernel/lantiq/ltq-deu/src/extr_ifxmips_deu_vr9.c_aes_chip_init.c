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
struct TYPE_2__ {int SM; int ENDI; scalar_t__ ARS; scalar_t__ NDC; } ;
struct aes_t {TYPE_1__ controlr; } ;

/* Variables and functions */
 scalar_t__ AES_START ; 

void aes_chip_init (void)
{
    volatile struct aes_t *aes = (struct aes_t *) AES_START;

    // start crypto engine with write to ILR
    aes->controlr.SM = 1;
    aes->controlr.NDC = 0;
    asm("sync");
    aes->controlr.ENDI = 1;
    asm("sync");
    aes->controlr.ARS = 0;
	
}