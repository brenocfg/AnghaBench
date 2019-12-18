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
typedef  int /*<<< orphan*/  WPACKET ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int BN_bn2binpad (int /*<<< orphan*/  const*,unsigned char*,int) ; 
 scalar_t__ BN_is_negative (int /*<<< orphan*/  const*) ; 
 int BN_num_bits (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ID_INTEGER ; 
 int /*<<< orphan*/  WPACKET_allocate_bytes (int /*<<< orphan*/ *,size_t,unsigned char**) ; 
 int /*<<< orphan*/  WPACKET_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_start_sub_packet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  encode_der_length (int /*<<< orphan*/ *,size_t) ; 

int encode_der_integer(WPACKET *pkt, const BIGNUM *n)
{
    unsigned char *bnbytes;
    size_t cont_len;

    if (BN_is_negative(n))
        return 0;

    /*
     * Calculate the ASN.1 INTEGER DER content length for n.
     * This is the number of whole bytes required to represent n (i.e. rounded
     * down), plus one.
     * If n is zero then the content is a single zero byte (length = 1).
     * If the number of bits of n is a multiple of 8 then an extra zero padding
     * byte is included to ensure that the value is still treated as positive
     * in the INTEGER two's complement representation.
     */
    cont_len = BN_num_bits(n) / 8 + 1;

    if (!WPACKET_start_sub_packet(pkt)
            || !WPACKET_put_bytes_u8(pkt, ID_INTEGER)
            || !encode_der_length(pkt, cont_len)
            || !WPACKET_allocate_bytes(pkt, cont_len, &bnbytes)
            || !WPACKET_close(pkt))
        return 0;

    if (bnbytes != NULL
            && BN_bn2binpad(n, bnbytes, (int)cont_len) != (int)cont_len)
        return 0;

    return 1;
}