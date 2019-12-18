#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_3__ {scalar_t__ commandType; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_1__ Query ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ CMD_SELECT ; 
 int DatumGetBool (int /*<<< orphan*/ ) ; 
 char DatumGetChar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetObjectId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int SPI_fnumber (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SPI_getbinval (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 char* SPI_getvalue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  appendStringInfoChar (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  get_query_def (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ linitial (int /*<<< orphan*/ *) ; 
 int list_length (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ stringToNode (char*) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
make_viewdef(StringInfo buf, HeapTuple ruletup, TupleDesc rulettc,
			 int prettyFlags, int wrapColumn)
{
	Query	   *query;
	char		ev_type;
	Oid			ev_class;
	bool		is_instead;
	char	   *ev_qual;
	char	   *ev_action;
	List	   *actions = NIL;
	Relation	ev_relation;
	int			fno;
	Datum		dat;
	bool		isnull;

	/*
	 * Get the attribute values from the rules tuple
	 */
	fno = SPI_fnumber(rulettc, "ev_type");
	dat = SPI_getbinval(ruletup, rulettc, fno, &isnull);
	Assert(!isnull);
	ev_type = DatumGetChar(dat);

	fno = SPI_fnumber(rulettc, "ev_class");
	dat = SPI_getbinval(ruletup, rulettc, fno, &isnull);
	Assert(!isnull);
	ev_class = DatumGetObjectId(dat);

	fno = SPI_fnumber(rulettc, "is_instead");
	dat = SPI_getbinval(ruletup, rulettc, fno, &isnull);
	Assert(!isnull);
	is_instead = DatumGetBool(dat);

	/* these could be nulls */
	fno = SPI_fnumber(rulettc, "ev_qual");
	ev_qual = SPI_getvalue(ruletup, rulettc, fno);

	fno = SPI_fnumber(rulettc, "ev_action");
	ev_action = SPI_getvalue(ruletup, rulettc, fno);
	if (ev_action != NULL)
		actions = (List *) stringToNode(ev_action);

	if (list_length(actions) != 1)
	{
		/* keep output buffer empty and leave */
		return;
	}

	query = (Query *) linitial(actions);

	if (ev_type != '1' || !is_instead ||
		strcmp(ev_qual, "<>") != 0 || query->commandType != CMD_SELECT)
	{
		/* keep output buffer empty and leave */
		return;
	}

	ev_relation = table_open(ev_class, AccessShareLock);

	get_query_def(query, buf, NIL, RelationGetDescr(ev_relation),
				  prettyFlags, wrapColumn, 0);
	appendStringInfoChar(buf, ';');

	table_close(ev_relation, AccessShareLock);
}