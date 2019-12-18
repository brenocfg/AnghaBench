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
 unsigned int sctp_checksum (char const*,int) ; 

int
sctp_selftest(void)
{
    const char testcase[] = 
        "\xd1\x60\x00\x50\x00\x00\x00\x00\x58\xe4\x5d\x36\x01\x00\x00\x14"
        "\x9e\x8d\x52\x25\x00\x00\x80\x00\x00\x0a\x08\x00\x46\x1a\xdf\x3d";

    unsigned xsum;

    xsum = sctp_checksum(testcase, 32);
    
    if (xsum != 0x58e45d36)
        return 1;

    return 0;
}