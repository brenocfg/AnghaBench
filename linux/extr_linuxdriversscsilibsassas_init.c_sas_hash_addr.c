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
typedef  int u8 ;
typedef  int u32 ;

/* Variables and functions */

void sas_hash_addr(u8 *hashed, const u8 *sas_addr)
{
        const u32 poly = 0x00DB2777;
        u32     r = 0;
        int     i;

        for (i = 0; i < 8; i++) {
                int b;
                for (b = 7; b >= 0; b--) {
                        r <<= 1;
                        if ((1 << b) & sas_addr[i]) {
                                if (!(r & 0x01000000))
                                        r ^= poly;
                        } else if (r & 0x01000000)
                                r ^= poly;
                }
        }

        hashed[0] = (r >> 16) & 0xFF;
        hashed[1] = (r >> 8) & 0xFF ;
        hashed[2] = r & 0xFF;
}