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
coap_udp_set_cookie(unsigned char *px, size_t length, uint64_t seqno)
{
    /*
     The frame header is 4 bytes long, with bytes 2 and 3 being
     the Message ID.
     We can also put up to 8 bytes of a "token" here instead of
     just using the message ID.
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |Ver| T |  TKL  |      Code     |          Message ID           |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |   Token (if any, TKL bytes) ...
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    */

    if (length < 4)
        return 0;

    px[2] = (unsigned char)(seqno >> 8);
    px[3] = (unsigned char)(seqno >> 0);

    return 0;
}