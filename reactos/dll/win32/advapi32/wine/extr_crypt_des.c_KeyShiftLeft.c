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

/* Variables and functions */
 int /*<<< orphan*/  CLRBIT (unsigned char*,int) ; 
 scalar_t__ GETBIT (unsigned char*,int) ; 
 int /*<<< orphan*/  SETBIT (unsigned char*,int) ; 

__attribute__((used)) static void KeyShiftLeft( unsigned char *key, const int numbits )
{
    int i;
    unsigned char keep = key[0];

    for (i = 0; i < numbits; i++)
    {
        int j;

        for (j = 0; j < 7; j++)
        {
            if (j && (key[j] & 0x80))
                key[j-1] |=  0x01;
            key[j] <<= 1;
        }

        if (GETBIT( key, 27 ))
        {
            CLRBIT( key, 27 );
            SETBIT( key, 55 );
        }

        if (keep & 0x80)
            SETBIT( key, 27 );

        keep <<= 1;
    }
}