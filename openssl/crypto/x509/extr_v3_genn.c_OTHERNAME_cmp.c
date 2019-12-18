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
struct TYPE_4__ {int /*<<< orphan*/  value; int /*<<< orphan*/  type_id; } ;
typedef  TYPE_1__ OTHERNAME ;

/* Variables and functions */
 int ASN1_TYPE_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int OBJ_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int OTHERNAME_cmp(OTHERNAME *a, OTHERNAME *b)
{
    int result = -1;

    if (!a || !b)
        return -1;
    /* Check their type first. */
    if ((result = OBJ_cmp(a->type_id, b->type_id)) != 0)
        return result;
    /* Check the value. */
    result = ASN1_TYPE_cmp(a->value, b->value);
    return result;
}