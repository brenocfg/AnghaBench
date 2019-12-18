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
struct BannerOutput {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  banout_append_char (struct BannerOutput*,unsigned int,char) ; 

void
banout_append_hexint(struct BannerOutput *banout, unsigned proto, unsigned long long number, int digits)
{
    if (digits == 0) {
        for (digits=16; digits>0; digits--)
            if (number>>((digits-1)*4) & 0xF)
                break;
    }
    
    for (;digits>0; digits--) {
        char c = "0123456789abcdef"[(number>>(unsigned long long)((digits-1)*4)) & 0xF];
        banout_append_char(banout, proto, c);
    }
}