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
typedef  int /*<<< orphan*/  Relids ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  bms_free (int /*<<< orphan*/ ) ; 
 int bms_num_members (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pull_varnos (int /*<<< orphan*/ *) ; 

int
NumRelids(Node *clause)
{
	Relids		varnos = pull_varnos(clause);
	int			result = bms_num_members(varnos);

	bms_free(varnos);
	return result;
}