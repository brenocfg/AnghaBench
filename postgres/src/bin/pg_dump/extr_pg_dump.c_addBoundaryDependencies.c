#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  separate; } ;
struct TYPE_8__ {int objType; int /*<<< orphan*/  dumpId; } ;
struct TYPE_7__ {int /*<<< orphan*/  separate; } ;
typedef  TYPE_1__ RuleInfo ;
typedef  TYPE_2__ DumpableObject ;
typedef  TYPE_3__ ConstraintInfo ;

/* Variables and functions */
#define  DO_ACCESS_METHOD 171 
#define  DO_AGG 170 
#define  DO_ATTRDEF 169 
#define  DO_BLOB 168 
#define  DO_BLOB_DATA 167 
#define  DO_CAST 166 
#define  DO_COLLATION 165 
#define  DO_CONSTRAINT 164 
#define  DO_CONVERSION 163 
#define  DO_DEFAULT_ACL 162 
#define  DO_DUMMY_TYPE 161 
#define  DO_EVENT_TRIGGER 160 
#define  DO_EXTENSION 159 
#define  DO_FDW 158 
#define  DO_FK_CONSTRAINT 157 
#define  DO_FOREIGN_SERVER 156 
#define  DO_FUNC 155 
#define  DO_INDEX 154 
#define  DO_INDEX_ATTACH 153 
#define  DO_NAMESPACE 152 
#define  DO_OPCLASS 151 
#define  DO_OPERATOR 150 
#define  DO_OPFAMILY 149 
#define  DO_POLICY 148 
#define  DO_POST_DATA_BOUNDARY 147 
#define  DO_PRE_DATA_BOUNDARY 146 
#define  DO_PROCLANG 145 
#define  DO_PUBLICATION 144 
#define  DO_PUBLICATION_REL 143 
#define  DO_REFRESH_MATVIEW 142 
#define  DO_RULE 141 
#define  DO_SEQUENCE_SET 140 
#define  DO_SHELL_TYPE 139 
#define  DO_STATSEXT 138 
#define  DO_SUBSCRIPTION 137 
#define  DO_TABLE 136 
#define  DO_TABLE_DATA 135 
#define  DO_TRANSFORM 134 
#define  DO_TRIGGER 133 
#define  DO_TSCONFIG 132 
#define  DO_TSDICT 131 
#define  DO_TSPARSER 130 
#define  DO_TSTEMPLATE 129 
#define  DO_TYPE 128 
 int /*<<< orphan*/  addObjectDependency (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
addBoundaryDependencies(DumpableObject **dobjs, int numObjs,
						DumpableObject *boundaryObjs)
{
	DumpableObject *preDataBound = boundaryObjs + 0;
	DumpableObject *postDataBound = boundaryObjs + 1;
	int			i;

	for (i = 0; i < numObjs; i++)
	{
		DumpableObject *dobj = dobjs[i];

		/*
		 * The classification of object types here must match the SECTION_xxx
		 * values assigned during subsequent ArchiveEntry calls!
		 */
		switch (dobj->objType)
		{
			case DO_NAMESPACE:
			case DO_EXTENSION:
			case DO_TYPE:
			case DO_SHELL_TYPE:
			case DO_FUNC:
			case DO_AGG:
			case DO_OPERATOR:
			case DO_ACCESS_METHOD:
			case DO_OPCLASS:
			case DO_OPFAMILY:
			case DO_COLLATION:
			case DO_CONVERSION:
			case DO_TABLE:
			case DO_ATTRDEF:
			case DO_PROCLANG:
			case DO_CAST:
			case DO_DUMMY_TYPE:
			case DO_TSPARSER:
			case DO_TSDICT:
			case DO_TSTEMPLATE:
			case DO_TSCONFIG:
			case DO_FDW:
			case DO_FOREIGN_SERVER:
			case DO_TRANSFORM:
			case DO_BLOB:
				/* Pre-data objects: must come before the pre-data boundary */
				addObjectDependency(preDataBound, dobj->dumpId);
				break;
			case DO_TABLE_DATA:
			case DO_SEQUENCE_SET:
			case DO_BLOB_DATA:
				/* Data objects: must come between the boundaries */
				addObjectDependency(dobj, preDataBound->dumpId);
				addObjectDependency(postDataBound, dobj->dumpId);
				break;
			case DO_INDEX:
			case DO_INDEX_ATTACH:
			case DO_STATSEXT:
			case DO_REFRESH_MATVIEW:
			case DO_TRIGGER:
			case DO_EVENT_TRIGGER:
			case DO_DEFAULT_ACL:
			case DO_POLICY:
			case DO_PUBLICATION:
			case DO_PUBLICATION_REL:
			case DO_SUBSCRIPTION:
				/* Post-data objects: must come after the post-data boundary */
				addObjectDependency(dobj, postDataBound->dumpId);
				break;
			case DO_RULE:
				/* Rules are post-data, but only if dumped separately */
				if (((RuleInfo *) dobj)->separate)
					addObjectDependency(dobj, postDataBound->dumpId);
				break;
			case DO_CONSTRAINT:
			case DO_FK_CONSTRAINT:
				/* Constraints are post-data, but only if dumped separately */
				if (((ConstraintInfo *) dobj)->separate)
					addObjectDependency(dobj, postDataBound->dumpId);
				break;
			case DO_PRE_DATA_BOUNDARY:
				/* nothing to do */
				break;
			case DO_POST_DATA_BOUNDARY:
				/* must come after the pre-data boundary */
				addObjectDependency(dobj, preDataBound->dumpId);
				break;
		}
	}
}