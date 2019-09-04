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
 int /*<<< orphan*/  CRC32C (unsigned int,unsigned char const) ; 

unsigned
sctp_checksum(const void *vbuffer, size_t length)
{
    const unsigned char *buffer = (const unsigned char *)vbuffer;
    unsigned i;
    unsigned crc32 = (unsigned)~0;
    unsigned result;
    unsigned char byte0,byte1,byte2,byte3;

    for (i = 0; i < 8; i++) {
        CRC32C(crc32, buffer[i]);
    }

    CRC32C(crc32, 0);
    CRC32C(crc32, 0);
    CRC32C(crc32, 0);
    CRC32C(crc32, 0);

    for (i = 12; i < length; i++) {
        CRC32C(crc32, buffer[i]);
    }
    result = ~crc32;

    /*  result  now holds the negated polynomial remainder;
    *  since the table and algorithm is "reflected" [williams95].
    *  That is,  result has the same value as if we mapped the message
    *  to a polynomial, computed the host-bit-order polynomial
    *  remainder, performed final negation, then did an end-for-end
    *  bit-reversal.
    *  Note that a 32-bit bit-reversal is identical to four inplace
    *  8-bit reversals followed by an end-for-end byteswap.
    *  In other words, the bytes of each bit are in the right order,
    *  but the bytes have been byteswapped.  So we now do an explicit
    *  byteswap.  On a little-endian machine, this byteswap and
    *  the final ntohl cancel out and could be elided.
    */

    byte0 = result & 0xff;
    byte1 = (result>>8) & 0xff;
    byte2 = (result>>16) & 0xff;
    byte3 = (result>>24) & 0xff;

    crc32 = ((byte0 << 24) |
            (byte1 << 16) |
            (byte2 << 8)  |
            byte3);
    return ( crc32 );
}