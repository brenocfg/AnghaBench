#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned char* data; int length; } ;
typedef  TYPE_1__ ASN1_BIT_STRING ;

/* Variables and functions */

int ASN1_BIT_STRING_check(const ASN1_BIT_STRING *a,
                          const unsigned char *flags, int flags_len)
{
    int i, ok;
    /* Check if there is one bit set at all. */
    if (!a || !a->data)
        return 1;

    /*
     * Check each byte of the internal representation of the bit string.
     */
    ok = 1;
    for (i = 0; i < a->length && ok; ++i) {
        unsigned char mask = i < flags_len ? ~flags[i] : 0xff;
        /* We are done if there is an unneeded bit set. */
        ok = (a->data[i] & mask) == 0;
    }
    return ok;
}