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
struct TYPE_3__ {long minsize; long maxsize; unsigned long mask; unsigned long flags; } ;
typedef  TYPE_1__ ASN1_STRING_TABLE ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_F_ASN1_STRING_TABLE_ADD ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 unsigned long STABLE_FLAGS_MALLOC ; 
 TYPE_1__* stable_get (int) ; 

int ASN1_STRING_TABLE_add(int nid,
                          long minsize, long maxsize, unsigned long mask,
                          unsigned long flags)
{
    ASN1_STRING_TABLE *tmp;

    tmp = stable_get(nid);
    if (tmp == NULL) {
        ASN1err(ASN1_F_ASN1_STRING_TABLE_ADD, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    if (minsize >= 0)
        tmp->minsize = minsize;
    if (maxsize >= 0)
        tmp->maxsize = maxsize;
    if (mask)
        tmp->mask = mask;
    if (flags)
        tmp->flags = STABLE_FLAGS_MALLOC | flags;
    return 1;
}