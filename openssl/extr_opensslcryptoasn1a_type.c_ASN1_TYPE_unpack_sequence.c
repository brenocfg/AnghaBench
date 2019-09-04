#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * sequence; } ;
struct TYPE_5__ {scalar_t__ type; TYPE_1__ value; } ;
typedef  TYPE_2__ ASN1_TYPE ;
typedef  int /*<<< orphan*/  ASN1_ITEM ;

/* Variables and functions */
 void* ASN1_item_unpack (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 scalar_t__ V_ASN1_SEQUENCE ; 

void *ASN1_TYPE_unpack_sequence(const ASN1_ITEM *it, const ASN1_TYPE *t)
{
    if (t == NULL || t->type != V_ASN1_SEQUENCE || t->value.sequence == NULL)
        return NULL;
    return ASN1_item_unpack(t->value.sequence, it);
}