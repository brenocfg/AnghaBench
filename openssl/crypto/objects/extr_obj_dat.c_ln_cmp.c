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
struct TYPE_5__ {int /*<<< orphan*/  ln; } ;
struct TYPE_4__ {int /*<<< orphan*/  ln; } ;
typedef  TYPE_1__ ASN1_OBJECT ;

/* Variables and functions */
 TYPE_2__* nid_objs ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ln_cmp(const ASN1_OBJECT *const *a, const unsigned int *b)
{
    return strcmp((*a)->ln, nid_objs[*b].ln);
}