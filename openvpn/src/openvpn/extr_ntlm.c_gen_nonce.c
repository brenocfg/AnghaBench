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
 scalar_t__ get_random () ; 

__attribute__((used)) static void
gen_nonce(unsigned char *nonce)
{
    /* Generates 8 random bytes to be used as client nonce */
    int i;

    for (i = 0; i<8; i++)
    {
        nonce[i] = (unsigned char)get_random();
    }
}