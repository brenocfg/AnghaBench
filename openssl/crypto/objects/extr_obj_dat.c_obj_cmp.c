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
struct TYPE_4__ {int length; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ ASN1_OBJECT ;

/* Variables and functions */
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__* nid_objs ; 

__attribute__((used)) static int obj_cmp(const ASN1_OBJECT *const *ap, const unsigned int *bp)
{
    int j;
    const ASN1_OBJECT *a = *ap;
    const ASN1_OBJECT *b = &nid_objs[*bp];

    j = (a->length - b->length);
    if (j)
        return j;
    if (a->length == 0)
        return 0;
    return memcmp(a->data, b->data, a->length);
}