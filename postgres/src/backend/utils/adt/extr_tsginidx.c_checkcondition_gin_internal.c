#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int* need_recheck; int* map_item_operand; int /*<<< orphan*/ * check; int /*<<< orphan*/ * first_item; } ;
struct TYPE_5__ {scalar_t__ weight; } ;
typedef  TYPE_1__ QueryOperand ;
typedef  int /*<<< orphan*/  QueryItem ;
typedef  int /*<<< orphan*/  GinTernaryValue ;
typedef  TYPE_2__ GinChkVal ;
typedef  int /*<<< orphan*/  ExecPhraseData ;

/* Variables and functions */

__attribute__((used)) static GinTernaryValue
checkcondition_gin_internal(GinChkVal *gcv, QueryOperand *val, ExecPhraseData *data)
{
	int			j;

	/*
	 * if any val requiring a weight is used or caller needs position
	 * information then set recheck flag
	 */
	if (val->weight != 0 || data != NULL)
		*(gcv->need_recheck) = true;

	/* convert item's number to corresponding entry's (operand's) number */
	j = gcv->map_item_operand[((QueryItem *) val) - gcv->first_item];

	/* return presence of current entry in indexed value */
	return gcv->check[j];
}