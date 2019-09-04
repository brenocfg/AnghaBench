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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 scalar_t__ ABS_INT64_MIN ; 
 int /*<<< orphan*/  ASN1_F_ASN1_GET_INT64 ; 
 int /*<<< orphan*/  ASN1_R_TOO_LARGE ; 
 int /*<<< orphan*/  ASN1_R_TOO_SMALL ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ INT64_MAX ; 
 scalar_t__ asn1_get_uint64 (scalar_t__*,unsigned char const*,size_t) ; 

__attribute__((used)) static int asn1_get_int64(int64_t *pr, const unsigned char *b, size_t blen,
                          int neg)
{
    uint64_t r;
    if (asn1_get_uint64(&r, b, blen) == 0)
        return 0;
    if (neg) {
        if (r <= INT64_MAX) {
            /* Most significant bit is guaranteed to be clear, negation
             * is guaranteed to be meaningful in platform-neutral sense. */
            *pr = -(int64_t)r;
        } else if (r == ABS_INT64_MIN) {
            /* This never happens if INT64_MAX == ABS_INT64_MIN, e.g.
             * on ones'-complement system. */
            *pr = (int64_t)(0 - r);
        } else {
            ASN1err(ASN1_F_ASN1_GET_INT64, ASN1_R_TOO_SMALL);
            return 0;
        }
    } else {
        if (r <= INT64_MAX) {
            *pr = (int64_t)r;
        } else {
            ASN1err(ASN1_F_ASN1_GET_INT64, ASN1_R_TOO_LARGE);
            return 0;
        }
    }
    return 1;
}