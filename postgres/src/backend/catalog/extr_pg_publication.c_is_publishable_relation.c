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
struct TYPE_4__ {int /*<<< orphan*/  rd_rel; } ;
typedef  TYPE_1__* Relation ;

/* Variables and functions */
 int /*<<< orphan*/  RelationGetRelid (TYPE_1__*) ; 
 int is_publishable_class (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
is_publishable_relation(Relation rel)
{
	return is_publishable_class(RelationGetRelid(rel), rel->rd_rel);
}