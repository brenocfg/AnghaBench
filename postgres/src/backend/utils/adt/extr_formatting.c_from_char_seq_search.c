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
 int /*<<< orphan*/  Assert (int) ; 
 int DCH_MAX_ITEM_SIZ ; 
 int /*<<< orphan*/  ERRCODE_INVALID_DATETIME_FORMAT ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*) ; 
 int /*<<< orphan*/  errmsg (char*,char*,int /*<<< orphan*/ ) ; 
 int seq_search (char*,char const* const*,int,int,int*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 

__attribute__((used)) static int
from_char_seq_search(int *dest, char **src, const char *const *array, int type,
					 int max, FormatNode *node, bool *have_error)
{
	int			len;

	*dest = seq_search(*src, array, type, max, &len);
	if (len <= 0)
	{
		char		copy[DCH_MAX_ITEM_SIZ + 1];

		Assert(max <= DCH_MAX_ITEM_SIZ);
		strlcpy(copy, *src, max + 1);

		RETURN_ERROR(ereport(ERROR,
							 (errcode(ERRCODE_INVALID_DATETIME_FORMAT),
							  errmsg("invalid value \"%s\" for \"%s\"",
									 copy, node->key->name),
							  errdetail("The given value did not match any of "
										"the allowed values for this field."))));
	}
	*src += len;
	return len;

on_error:
	return -1;
}