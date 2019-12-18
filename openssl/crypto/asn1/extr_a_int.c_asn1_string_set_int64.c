#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  tbuf ;
typedef  int /*<<< orphan*/  r ;
typedef  scalar_t__ int64_t ;
struct TYPE_4__ {int type; } ;
typedef  TYPE_1__ ASN1_STRING ;

/* Variables and functions */
 int ASN1_STRING_set (TYPE_1__*,unsigned char*,int) ; 
 int V_ASN1_NEG ; 
 size_t asn1_put_uint64 (unsigned char*,scalar_t__) ; 

__attribute__((used)) static int asn1_string_set_int64(ASN1_STRING *a, int64_t r, int itype)
{
    unsigned char tbuf[sizeof(r)];
    size_t off;

    a->type = itype;
    if (r < 0) {
        /* Most obvious '-r' triggers undefined behaviour for most
         * common INT64_MIN. Even though below '0 - (uint64_t)r' can
         * appear two's-complement centric, it does produce correct/
         * expected result even on one's-complement. This is because
         * cast to unsigned has to change bit pattern... */
        off = asn1_put_uint64(tbuf, 0 - (uint64_t)r);
        a->type |= V_ASN1_NEG;
    } else {
        off = asn1_put_uint64(tbuf, r);
        a->type &= ~V_ASN1_NEG;
    }
    return ASN1_STRING_set(a, tbuf + off, sizeof(tbuf) - off);
}