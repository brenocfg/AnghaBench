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
typedef  int /*<<< orphan*/  PACKET ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 unsigned int ID_SEQUENCE ; 
 int /*<<< orphan*/  PACKET_buf_init (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 unsigned char const* PACKET_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_get_1 (int /*<<< orphan*/ *,unsigned int*) ; 
 scalar_t__ PACKET_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decode_der_integer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decode_der_length (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

size_t decode_der_dsa_sig(BIGNUM *r, BIGNUM *s, const unsigned char **ppin,
                          size_t len)
{
    size_t consumed;
    PACKET pkt, contpkt;
    unsigned int tag;

    if (!PACKET_buf_init(&pkt, *ppin, len)
            || !PACKET_get_1(&pkt, &tag)
            || tag != ID_SEQUENCE
            || !decode_der_length(&pkt, &contpkt)
            || !decode_der_integer(&contpkt, r)
            || !decode_der_integer(&contpkt, s)
            || PACKET_remaining(&contpkt) != 0)
        return 0;

    consumed = PACKET_data(&pkt) - *ppin;
    *ppin += consumed;
    return consumed;
}