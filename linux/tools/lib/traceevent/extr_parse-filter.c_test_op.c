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
struct tep_record {int dummy; } ;
struct TYPE_2__ {int type; int /*<<< orphan*/  right; int /*<<< orphan*/  left; } ;
struct tep_filter_arg {TYPE_1__ op; } ;
struct tep_event {int dummy; } ;
typedef  enum tep_errno { ____Placeholder_tep_errno } tep_errno ;

/* Variables and functions */
 int TEP_ERRNO__INVALID_OP_TYPE ; 
#define  TEP_FILTER_OP_AND 130 
#define  TEP_FILTER_OP_NOT 129 
#define  TEP_FILTER_OP_OR 128 
 int /*<<< orphan*/  test_filter (struct tep_event*,int /*<<< orphan*/ ,struct tep_record*,int*) ; 

__attribute__((used)) static int test_op(struct tep_event *event, struct tep_filter_arg *arg,
		   struct tep_record *record, enum tep_errno *err)
{
	switch (arg->op.type) {
	case TEP_FILTER_OP_AND:
		return test_filter(event, arg->op.left, record, err) &&
			test_filter(event, arg->op.right, record, err);

	case TEP_FILTER_OP_OR:
		return test_filter(event, arg->op.left, record, err) ||
			test_filter(event, arg->op.right, record, err);

	case TEP_FILTER_OP_NOT:
		return !test_filter(event, arg->op.right, record, err);

	default:
		if (!*err)
			*err = TEP_ERRNO__INVALID_OP_TYPE;
		return 0;
	}
}