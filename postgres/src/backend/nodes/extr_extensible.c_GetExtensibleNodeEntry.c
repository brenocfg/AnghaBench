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
struct TYPE_2__ {void const* extnodemethods; } ;
typedef  int /*<<< orphan*/  HTAB ;
typedef  TYPE_1__ ExtensibleNodeEntry ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_UNDEFINED_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HASH_FIND ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 scalar_t__ hash_search (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const void *
GetExtensibleNodeEntry(HTAB *htable, const char *extnodename, bool missing_ok)
{
	ExtensibleNodeEntry *entry = NULL;

	if (htable != NULL)
		entry = (ExtensibleNodeEntry *) hash_search(htable,
													extnodename,
													HASH_FIND, NULL);
	if (!entry)
	{
		if (missing_ok)
			return NULL;
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_OBJECT),
				 errmsg("ExtensibleNodeMethods \"%s\" was not registered",
						extnodename)));
	}

	return entry->extnodemethods;
}