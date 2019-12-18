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
typedef  int /*<<< orphan*/  modlabel ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  ConstraintNameExists (char*,int /*<<< orphan*/ ) ; 
 int NAMEDATALEN ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrNCpy (char*,char const*,int) ; 
 int /*<<< orphan*/  get_relname_relid (char*,int /*<<< orphan*/ ) ; 
 char* makeObjectName (char const*,char const*,char*) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,int) ; 

char *
ChooseRelationName(const char *name1, const char *name2,
				   const char *label, Oid namespaceid,
				   bool isconstraint)
{
	int			pass = 0;
	char	   *relname = NULL;
	char		modlabel[NAMEDATALEN];

	/* try the unmodified label first */
	StrNCpy(modlabel, label, sizeof(modlabel));

	for (;;)
	{
		relname = makeObjectName(name1, name2, modlabel);

		if (!OidIsValid(get_relname_relid(relname, namespaceid)))
		{
			if (!isconstraint ||
				!ConstraintNameExists(relname, namespaceid))
				break;
		}

		/* found a conflict, so try a new name component */
		pfree(relname);
		snprintf(modlabel, sizeof(modlabel), "%s%d", label, ++pass);
	}

	return relname;
}