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
 int /*<<< orphan*/  ASSERT (int) ; 
 int HWREG (scalar_t__) ; 
 scalar_t__ SHAMD5_BASE ; 
 int SHAMD5_MODE_ALGO_M ; 
#define  SHAMD5_MODE_ALGO_MD5 131 
#define  SHAMD5_MODE_ALGO_SHA1 130 
#define  SHAMD5_MODE_ALGO_SHA224 129 
#define  SHAMD5_MODE_ALGO_SHA256 128 
 scalar_t__ SHAMD5_O_IDIGEST_A ; 
 scalar_t__ SHAMD5_O_MODE ; 

void
SHAMD5ResultRead(uint32_t ui32Base, uint8_t *pui8Dest)
{
    uint32_t ui32Idx, ui32Count;

    //
    // Check the arguments.
    //
    ASSERT(ui32Base == SHAMD5_BASE);

    //
    // Determine the number of bytes in the result, based on the hash type.
    //
    switch(HWREG(ui32Base + SHAMD5_O_MODE) & SHAMD5_MODE_ALGO_M)
    {
        //
        // The MD5 hash is being used.
        //
        case SHAMD5_MODE_ALGO_MD5:
        {
            //
            // There are 16 bytes in the MD5 hash.
            //
            ui32Count = 16;

            //
            // Done.
            //
            break;
        }

        //
        // The SHA-1 hash is being used.
        //
        case SHAMD5_MODE_ALGO_SHA1:
        {
            //
            // There are 20 bytes in the SHA-1 hash.
            //
            ui32Count = 20;

            //
            // Done.
            //
            break;
        }

        //
        // The SHA-224 hash is being used.
        //
        case SHAMD5_MODE_ALGO_SHA224:
        {
            //
            // There are 28 bytes in the SHA-224 hash.
            //
            ui32Count = 28;

            //
            // Done.
            //
            break;
        }

        //
        // The SHA-256 hash is being used.
        //
        case SHAMD5_MODE_ALGO_SHA256:
        {
            //
            // There are 32 bytes in the SHA-256 hash.
            //
            ui32Count = 32;

            //
            // Done.
            //
            break;
        }

        //
        // The hash type is not recognized.
        //
        default:
        {
            //
            // Return without reading a result since the hardware appears to be
            // misconfigured.
            //
            return;
        }
    }

    //
    // Read the hash result.
    //
    for(ui32Idx = 0; ui32Idx < ui32Count; ui32Idx += 4)
    {
    	*((uint32_t *)(pui8Dest+ui32Idx)) =
                                HWREG(ui32Base + SHAMD5_O_IDIGEST_A + ui32Idx);
    }
}