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
struct TYPE_4__ {int maxrefs; int /*<<< orphan*/ * extras; int /*<<< orphan*/ * refs; scalar_t__ numrefs; } ;
typedef  TYPE_1__ ObjectAddresses ;
typedef  int /*<<< orphan*/  ObjectAddress ;

/* Variables and functions */
 TYPE_1__* palloc (int) ; 

ObjectAddresses *
new_object_addresses(void)
{
	ObjectAddresses *addrs;

	addrs = palloc(sizeof(ObjectAddresses));

	addrs->numrefs = 0;
	addrs->maxrefs = 32;
	addrs->refs = (ObjectAddress *)
		palloc(addrs->maxrefs * sizeof(ObjectAddress));
	addrs->extras = NULL;		/* until/unless needed */

	return addrs;
}