#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  dumpId; TYPE_2__* namespace; int /*<<< orphan*/  name; } ;
struct TYPE_16__ {TYPE_4__ dobj; int /*<<< orphan*/  rolname; } ;
typedef  TYPE_5__ TableInfo ;
struct TYPE_14__ {int dump; int /*<<< orphan*/  dumpId; int /*<<< orphan*/  catId; int /*<<< orphan*/  name; } ;
struct TYPE_18__ {TYPE_3__ dobj; scalar_t__ separate; TYPE_5__* contable; } ;
struct TYPE_17__ {int /*<<< orphan*/  data; } ;
struct TYPE_12__ {int /*<<< orphan*/  name; } ;
struct TYPE_13__ {TYPE_1__ dobj; } ;
typedef  TYPE_6__* PQExpBuffer ;
typedef  TYPE_7__ ConstraintInfo ;
typedef  int /*<<< orphan*/  Archive ;

/* Variables and functions */
 int DUMP_COMPONENT_COMMENT ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_6__*,char*,int /*<<< orphan*/ ) ; 
 TYPE_6__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_6__*) ; 
 int /*<<< orphan*/  dumpComment (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmtId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* pg_strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dumpTableConstraintComment(Archive *fout, ConstraintInfo *coninfo)
{
	TableInfo  *tbinfo = coninfo->contable;
	PQExpBuffer conprefix = createPQExpBuffer();
	char	   *qtabname;

	qtabname = pg_strdup(fmtId(tbinfo->dobj.name));

	appendPQExpBuffer(conprefix, "CONSTRAINT %s ON",
					  fmtId(coninfo->dobj.name));

	if (coninfo->dobj.dump & DUMP_COMPONENT_COMMENT)
		dumpComment(fout, conprefix->data, qtabname,
					tbinfo->dobj.namespace->dobj.name,
					tbinfo->rolname,
					coninfo->dobj.catId, 0,
					coninfo->separate ? coninfo->dobj.dumpId : tbinfo->dobj.dumpId);

	destroyPQExpBuffer(conprefix);
	free(qtabname);
}