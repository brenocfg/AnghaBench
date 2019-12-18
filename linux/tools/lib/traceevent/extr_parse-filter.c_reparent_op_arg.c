#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct tep_filter_arg* left; struct tep_filter_arg* right; } ;
struct tep_filter_arg {scalar_t__ type; TYPE_1__ op; } ;
typedef  enum tep_errno { ____Placeholder_tep_errno } tep_errno ;

/* Variables and functions */
 int TEP_ERRNO__REPARENT_FAILED ; 
 int TEP_ERRNO__REPARENT_NOT_OP ; 
 scalar_t__ TEP_FILTER_ARG_OP ; 
 int /*<<< orphan*/  free (struct tep_filter_arg*) ; 
 int /*<<< orphan*/  free_arg (struct tep_filter_arg*) ; 
 int /*<<< orphan*/  show_error (char*,char*) ; 

__attribute__((used)) static enum tep_errno
reparent_op_arg(struct tep_filter_arg *parent, struct tep_filter_arg *old_child,
		struct tep_filter_arg *arg, char *error_str)
{
	struct tep_filter_arg *other_child;
	struct tep_filter_arg **ptr;

	if (parent->type != TEP_FILTER_ARG_OP &&
	    arg->type != TEP_FILTER_ARG_OP) {
		show_error(error_str, "can not reparent other than OP");
		return TEP_ERRNO__REPARENT_NOT_OP;
	}

	/* Get the sibling */
	if (old_child->op.right == arg) {
		ptr = &old_child->op.right;
		other_child = old_child->op.left;
	} else if (old_child->op.left == arg) {
		ptr = &old_child->op.left;
		other_child = old_child->op.right;
	} else {
		show_error(error_str, "Error in reparent op, find other child");
		return TEP_ERRNO__REPARENT_FAILED;
	}

	/* Detach arg from old_child */
	*ptr = NULL;

	/* Check for root */
	if (parent == old_child) {
		free_arg(other_child);
		*parent = *arg;
		/* Free arg without recussion */
		free(arg);
		return 0;
	}

	if (parent->op.right == old_child)
		ptr = &parent->op.right;
	else if (parent->op.left == old_child)
		ptr = &parent->op.left;
	else {
		show_error(error_str, "Error in reparent op");
		return TEP_ERRNO__REPARENT_FAILED;
	}

	*ptr = arg;

	free_arg(old_child);
	return 0;
}