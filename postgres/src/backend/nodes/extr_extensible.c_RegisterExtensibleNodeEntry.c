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
struct TYPE_6__ {void const* extnodemethods; } ;
struct TYPE_5__ {int entrysize; scalar_t__ keysize; } ;
typedef  int /*<<< orphan*/  HTAB ;
typedef  TYPE_1__ HASHCTL ;
typedef  TYPE_2__ ExtensibleNodeEntry ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_DUPLICATE_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ EXTNODENAME_MAX_LEN ; 
 int /*<<< orphan*/  HASH_ELEM ; 
 int /*<<< orphan*/  HASH_ENTER ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 int /*<<< orphan*/ * hash_create (char const*,int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ hash_search (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void
RegisterExtensibleNodeEntry(HTAB **p_htable, const char *htable_label,
							const char *extnodename,
							const void *extnodemethods)
{
	ExtensibleNodeEntry *entry;
	bool		found;

	if (*p_htable == NULL)
	{
		HASHCTL		ctl;

		memset(&ctl, 0, sizeof(HASHCTL));
		ctl.keysize = EXTNODENAME_MAX_LEN;
		ctl.entrysize = sizeof(ExtensibleNodeEntry);

		*p_htable = hash_create(htable_label, 100, &ctl, HASH_ELEM);
	}

	if (strlen(extnodename) >= EXTNODENAME_MAX_LEN)
		elog(ERROR, "extensible node name is too long");

	entry = (ExtensibleNodeEntry *) hash_search(*p_htable,
												extnodename,
												HASH_ENTER, &found);
	if (found)
		ereport(ERROR,
				(errcode(ERRCODE_DUPLICATE_OBJECT),
				 errmsg("extensible node type \"%s\" already exists",
						extnodename)));

	entry->extnodemethods = extnodemethods;
}