#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int length; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ DER_ENC ;

/* Variables and functions */
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int der_cmp(const void *a, const void *b)
{
    const DER_ENC *d1 = a, *d2 = b;
    int cmplen, i;
    cmplen = (d1->length < d2->length) ? d1->length : d2->length;
    i = memcmp(d1->data, d2->data, cmplen);
    if (i)
        return i;
    return d1->length - d2->length;
}