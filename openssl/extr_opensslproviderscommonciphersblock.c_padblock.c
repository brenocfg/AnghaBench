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

void padblock(unsigned char *buf, size_t *buflen, size_t blocksize)
{
    size_t i;
    unsigned char pad = (unsigned char)(blocksize - *buflen);

    for (i = *buflen; i < blocksize; i++)
        buf[i] = pad;
}