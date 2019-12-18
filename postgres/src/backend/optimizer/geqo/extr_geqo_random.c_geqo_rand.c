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
struct TYPE_5__ {int /*<<< orphan*/  random_state; } ;
struct TYPE_4__ {scalar_t__ join_search_private; } ;
typedef  TYPE_1__ PlannerInfo ;
typedef  TYPE_2__ GeqoPrivateData ;

/* Variables and functions */
 double pg_erand48 (int /*<<< orphan*/ ) ; 

double
geqo_rand(PlannerInfo *root)
{
	GeqoPrivateData *private = (GeqoPrivateData *) root->join_search_private;

	return pg_erand48(private->random_state);
}