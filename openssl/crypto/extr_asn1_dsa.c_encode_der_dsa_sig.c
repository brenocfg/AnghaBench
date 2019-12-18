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
 int /*<<< orphan*/  ID_SEQUENCE ; 
 int /*<<< orphan*/  WPACKET_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_get_length (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  WPACKET_init_null (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int WPACKET_is_null_buf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_start_sub_packet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  encode_der_integer (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  encode_der_length (int /*<<< orphan*/ *,size_t) ; 

int encode_der_dsa_sig(WPACKET *pkt, const BIGNUM *r, const BIGNUM *s)
{
    WPACKET tmppkt, *dummypkt;
    size_t cont_len;
    int isnull = WPACKET_is_null_buf(pkt);

    if (!WPACKET_start_sub_packet(pkt))
        return 0;

    if (!isnull) {
        if (!WPACKET_init_null(&tmppkt, 0))
            return 0;
        dummypkt = &tmppkt;
    } else {
        /* If the input packet has a NULL buffer, we don't need a dummy packet */
        dummypkt = pkt;
    }

    /* Calculate the content length */
    if (!encode_der_integer(dummypkt, r)
            || !encode_der_integer(dummypkt, s)
            || !WPACKET_get_length(dummypkt, &cont_len)
            || (!isnull && !WPACKET_finish(dummypkt))) {
        if (!isnull)
            WPACKET_cleanup(dummypkt);
        return 0;
    }

    /* Add the tag and length bytes */
    if (!WPACKET_put_bytes_u8(pkt, ID_SEQUENCE)
            || !encode_der_length(pkt, cont_len)
               /*
                * Really encode the integers. We already wrote to the main pkt
                * if it had a NULL buffer, so don't do it again
                */
            || (!isnull && !encode_der_integer(pkt, r))
            || (!isnull && !encode_der_integer(pkt, s))
            || !WPACKET_close(pkt))
        return 0;

    return 1;
}