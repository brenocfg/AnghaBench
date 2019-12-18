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
struct TYPE_4__ {int length; int type; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ ASN1_STRING ;

/* Variables and functions */
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int ASN1_STRING_cmp(const ASN1_STRING *a, const ASN1_STRING *b)
{
    int i;

    i = (a->length - b->length);
    if (i == 0) {
        i = memcmp(a->data, b->data, a->length);
        if (i == 0)
            return a->type - b->type;
        else
            return i;
    } else
        return i;
}