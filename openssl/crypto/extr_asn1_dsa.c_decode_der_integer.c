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
 int /*<<< orphan*/ * BN_bin2bn (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 unsigned int ID_INTEGER ; 
 int /*<<< orphan*/  PACKET_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_get_1 (int /*<<< orphan*/ *,unsigned int*) ; 
 scalar_t__ PACKET_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decode_der_length (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int decode_der_integer(PACKET *pkt, BIGNUM *n)
{
    PACKET contpkt, tmppkt;
    unsigned int tag, tmp;

    /* Check we have an integer and get the content bytes */
    if (!PACKET_get_1(pkt, &tag)
            || tag != ID_INTEGER
            || !decode_der_length(pkt, &contpkt))
        return 0;

    /* Peek ahead at the first bytes to check for proper encoding */
    tmppkt = contpkt;
    /* The INTEGER must be positive */
    if (!PACKET_get_1(&tmppkt, &tmp)
            || (tmp & 0x80) != 0)
        return 0;
    /* If there a zero padding byte the next byte must have the msb set */
    if (PACKET_remaining(&tmppkt) > 0 && tmp == 0) {
        if (!PACKET_get_1(&tmppkt, &tmp)
                || (tmp & 0x80) == 0)
            return 0;
    }

    if (BN_bin2bn(PACKET_data(&contpkt),
                  (int)PACKET_remaining(&contpkt), n) == NULL)
        return 0;

    return 1;
}