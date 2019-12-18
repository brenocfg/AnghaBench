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
 scalar_t__ AES_O_TAG_OUT_0 ; 
 scalar_t__ AES_O_TAG_OUT_1 ; 
 scalar_t__ AES_O_TAG_OUT_2 ; 
 scalar_t__ AES_O_TAG_OUT_3 ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ HWREG (scalar_t__) ; 

void
AESTagRead(uint32_t ui32Base, uint8_t *pui8TagData)
{
    //
    // Check the arguments.
    //
    ASSERT(ui32Base == AES_BASE);

    //
    // Read the tag data.
    //
    *((uint32_t *)(pui8TagData+0)) = HWREG((ui32Base + AES_O_TAG_OUT_0));
    *((uint32_t *)(pui8TagData+4)) = HWREG((ui32Base + AES_O_TAG_OUT_1));
    *((uint32_t *)(pui8TagData+8)) = HWREG((ui32Base + AES_O_TAG_OUT_2));
    *((uint32_t *)(pui8TagData+12)) = HWREG((ui32Base + AES_O_TAG_OUT_3));
}