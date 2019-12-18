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

/* Variables and functions */
 int HWREG (scalar_t__) ; 
 int /*<<< orphan*/  MAP_SHAMD5ResultRead (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ SHAMD5_BASE ; 
 int SHAMD5_INT_OUTPUT_READY ; 
 scalar_t__ SHAMD5_O_IRQSTATUS ; 

void CRYPTOHASH_SHAMD5Read (uint8_t *hash) {
    // wait for the output to be ready
    while((HWREG(SHAMD5_BASE + SHAMD5_O_IRQSTATUS) & SHAMD5_INT_OUTPUT_READY) == 0);
    // read the result
    MAP_SHAMD5ResultRead(SHAMD5_BASE, hash);
}