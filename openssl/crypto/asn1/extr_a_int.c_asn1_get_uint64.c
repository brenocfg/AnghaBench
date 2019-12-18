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
 int /*<<< orphan*/  ASN1_F_ASN1_GET_UINT64 ; 
 int /*<<< orphan*/  ASN1_R_TOO_LARGE ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int asn1_get_uint64(uint64_t *pr, const unsigned char *b, size_t blen)
{
    size_t i;
    uint64_t r;

    if (blen > sizeof(*pr)) {
        ASN1err(ASN1_F_ASN1_GET_UINT64, ASN1_R_TOO_LARGE);
        return 0;
    }
    if (b == NULL)
        return 0;
    for (r = 0, i = 0; i < blen; i++) {
        r <<= 8;
        r |= b[i];
    }
    *pr = r;
    return 1;
}