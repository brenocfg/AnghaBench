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
struct TYPE_5__ {TYPE_1__* key; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ FormatNode ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INVALID_DATETIME_FORMAT ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
from_char_set_int(int *dest, const int value, const FormatNode *node,
				  bool *have_error)
{
	if (*dest != 0 && *dest != value)
		RETURN_ERROR(ereport(ERROR,
							 (errcode(ERRCODE_INVALID_DATETIME_FORMAT),
							  errmsg("conflicting values for \"%s\" field in "
									 "formatting string",
									 node->key->name),
							  errdetail("This value contradicts a previous setting "
										"for the same field type."))));
	*dest = value;

on_error:
	return;
}