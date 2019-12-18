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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ AES_BASE ; 
 scalar_t__ AES_O_IV_IN_0 ; 
 scalar_t__ AES_O_IV_IN_1 ; 
 scalar_t__ AES_O_IV_IN_2 ; 
 scalar_t__ AES_O_IV_IN_3 ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ HWREG (scalar_t__) ; 

void
AESIVGet(uint32_t ui32Base, uint8_t *pui8IVdata)
{
    //
    // Check the arguments.
    //
    ASSERT(ui32Base == AES_BASE);

    //
    // Write the initial vector registers.
    //
    *((uint32_t *)(pui8IVdata+ 0)) = HWREG(ui32Base + AES_O_IV_IN_0);
    *((uint32_t *)(pui8IVdata+ 4)) = HWREG(ui32Base + AES_O_IV_IN_1);
    *((uint32_t *)(pui8IVdata+ 8)) = HWREG(ui32Base + AES_O_IV_IN_2);
    *((uint32_t *)(pui8IVdata+12)) = HWREG(ui32Base + AES_O_IV_IN_3);
}