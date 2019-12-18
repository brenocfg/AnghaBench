#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct resource {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 struct resource* insert_resource_conflict (struct resource*,struct resource*) ; 

int insert_resource(struct resource *parent, struct resource *new)
{
	struct resource *conflict;

	conflict = insert_resource_conflict(parent, new);
	return conflict ? -EBUSY : 0;
}