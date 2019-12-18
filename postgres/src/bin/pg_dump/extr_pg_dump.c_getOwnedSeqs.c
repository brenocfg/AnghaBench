#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  oid; } ;
struct TYPE_7__ {int dump; TYPE_1__ catId; } ;
struct TYPE_8__ {int interesting; TYPE_2__ dobj; scalar_t__ is_identity_sequence; int /*<<< orphan*/  owning_tab; } ;
typedef  TYPE_3__ TableInfo ;
typedef  int /*<<< orphan*/  Archive ;

/* Variables and functions */
 int DUMP_COMPONENT_NONE ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* findTableByOid (int /*<<< orphan*/ ) ; 

void
getOwnedSeqs(Archive *fout, TableInfo tblinfo[], int numTables)
{
	int			i;

	/*
	 * Force sequences that are "owned" by table columns to be dumped whenever
	 * their owning table is being dumped.
	 */
	for (i = 0; i < numTables; i++)
	{
		TableInfo  *seqinfo = &tblinfo[i];
		TableInfo  *owning_tab;

		if (!OidIsValid(seqinfo->owning_tab))
			continue;			/* not an owned sequence */

		owning_tab = findTableByOid(seqinfo->owning_tab);
		if (owning_tab == NULL)
			fatal("failed sanity check, parent table with OID %u of sequence with OID %u not found",
				  seqinfo->owning_tab, seqinfo->dobj.catId.oid);

		/*
		 * Only dump identity sequences if we're going to dump the table that
		 * it belongs to.
		 */
		if (owning_tab->dobj.dump == DUMP_COMPONENT_NONE &&
			seqinfo->is_identity_sequence)
		{
			seqinfo->dobj.dump = DUMP_COMPONENT_NONE;
			continue;
		}

		/*
		 * Otherwise we need to dump the components that are being dumped for
		 * the table and any components which the sequence is explicitly
		 * marked with.
		 *
		 * We can't simply use the set of components which are being dumped
		 * for the table as the table might be in an extension (and only the
		 * non-extension components, eg: ACLs if changed, security labels, and
		 * policies, are being dumped) while the sequence is not (and
		 * therefore the definition and other components should also be
		 * dumped).
		 *
		 * If the sequence is part of the extension then it should be properly
		 * marked by checkExtensionMembership() and this will be a no-op as
		 * the table will be equivalently marked.
		 */
		seqinfo->dobj.dump = seqinfo->dobj.dump | owning_tab->dobj.dump;

		if (seqinfo->dobj.dump != DUMP_COMPONENT_NONE)
			seqinfo->interesting = true;
	}
}