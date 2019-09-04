#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct gcov_iterator {int record; size_t type; size_t num_types; TYPE_1__* info; int /*<<< orphan*/  function; int /*<<< orphan*/  count; } ;
struct TYPE_6__ {int /*<<< orphan*/ * n_ctrs; } ;
struct TYPE_5__ {int /*<<< orphan*/  offset; } ;
struct TYPE_4__ {int /*<<< orphan*/  n_functions; } ;

/* Variables and functions */
 int EINVAL ; 
#define  RECORD_COUNT 137 
#define  RECORD_COUNT_LEN 136 
#define  RECORD_COUNT_TAG 135 
#define  RECORD_FILE_MAGIC 134 
#define  RECORD_FUNCTION_CHECK 133 
#define  RECORD_FUNCTION_IDENT 132 
#define  RECORD_FUNCTION_TAG 131 
#define  RECORD_FUNCTON_TAG_LEN 130 
#define  RECORD_GCOV_VERSION 129 
#define  RECORD_TIME_STAMP 128 
 TYPE_3__* get_func (struct gcov_iterator*) ; 
 TYPE_2__* get_type (struct gcov_iterator*) ; 

int gcov_iter_next(struct gcov_iterator *iter)
{
	switch (iter->record) {
	case RECORD_FILE_MAGIC:
	case RECORD_GCOV_VERSION:
	case RECORD_FUNCTION_TAG:
	case RECORD_FUNCTON_TAG_LEN:
	case RECORD_FUNCTION_IDENT:
	case RECORD_COUNT_TAG:
		/* Advance to next record */
		iter->record++;
		break;
	case RECORD_COUNT:
		/* Advance to next count */
		iter->count++;
		/* fall through */
	case RECORD_COUNT_LEN:
		if (iter->count < get_func(iter)->n_ctrs[iter->type]) {
			iter->record = 9;
			break;
		}
		/* Advance to next counter type */
		get_type(iter)->offset += iter->count;
		iter->count = 0;
		iter->type++;
		/* fall through */
	case RECORD_FUNCTION_CHECK:
		if (iter->type < iter->num_types) {
			iter->record = 7;
			break;
		}
		/* Advance to next function */
		iter->type = 0;
		iter->function++;
		/* fall through */
	case RECORD_TIME_STAMP:
		if (iter->function < iter->info->n_functions)
			iter->record = 3;
		else
			iter->record = -1;
		break;
	}
	/* Check for EOF. */
	if (iter->record == -1)
		return -EINVAL;
	else
		return 0;
}