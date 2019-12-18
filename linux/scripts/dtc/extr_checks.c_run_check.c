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
struct node {int dummy; } ;
struct dt_info {struct node* dt; } ;
struct check {int inprogress; scalar_t__ status; int num_prereqs; scalar_t__ error; int /*<<< orphan*/  name; struct check** prereq; } ;

/* Variables and functions */
 scalar_t__ PASSED ; 
 scalar_t__ PREREQ ; 
 int /*<<< orphan*/  TRACE (struct check*,char*,scalar_t__) ; 
 scalar_t__ UNCHECKED ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  check_msg (struct check*,struct dt_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_nodes_props (struct check*,struct dt_info*,struct node*) ; 

__attribute__((used)) static bool run_check(struct check *c, struct dt_info *dti)
{
	struct node *dt = dti->dt;
	bool error = false;
	int i;

	assert(!c->inprogress);

	if (c->status != UNCHECKED)
		goto out;

	c->inprogress = true;

	for (i = 0; i < c->num_prereqs; i++) {
		struct check *prq = c->prereq[i];
		error = error || run_check(prq, dti);
		if (prq->status != PASSED) {
			c->status = PREREQ;
			check_msg(c, dti, NULL, NULL, "Failed prerequisite '%s'",
				  c->prereq[i]->name);
		}
	}

	if (c->status != UNCHECKED)
		goto out;

	check_nodes_props(c, dti, dt);

	if (c->status == UNCHECKED)
		c->status = PASSED;

	TRACE(c, "\tCompleted, status %d", c->status);

out:
	c->inprogress = false;
	if ((c->status != PASSED) && (c->error))
		error = true;
	return error;
}