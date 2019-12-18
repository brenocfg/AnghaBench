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
typedef  int uint64_t ;

/* Variables and functions */

unsigned
memcached_udp_set_cookie(unsigned char *px, size_t length, uint64_t seqno)
{
    /*
    The frame header is 8 bytes long, as follows (all values are 16-bit integers
    in network byte order, high byte first):

    0-1 Request ID
    2-3 Sequence number
    4-5 Total number of datagrams in this message
    6-7 Reserved for future use; must be 0
    */

    if (length < 2)
        return 0;

    px[0] = (unsigned char)(seqno >> 8);
    px[1] = (unsigned char)(seqno >> 0);


    return 0;
}