#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_18__ {int /*<<< orphan*/  is_instead; int /*<<< orphan*/  ev_enabled; scalar_t__ ev_type; int /*<<< orphan*/  oid; } ;
struct TYPE_17__ {TYPE_2__* rd_rules; int /*<<< orphan*/ * rd_rulescxt; TYPE_1__* rd_rel; } ;
struct TYPE_16__ {int /*<<< orphan*/ * qual; int /*<<< orphan*/ * actions; int /*<<< orphan*/  isInstead; int /*<<< orphan*/  enabled; scalar_t__ event; int /*<<< orphan*/  ruleId; } ;
struct TYPE_15__ {int numLocks; TYPE_3__** rules; } ;
struct TYPE_14__ {int /*<<< orphan*/  relowner; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  TYPE_2__ RuleLock ;
typedef  TYPE_3__ RewriteRule ;
typedef  TYPE_4__* Relation ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/ * MemoryContext ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_5__* Form_pg_rewrite ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_SMALL_SIZES ; 
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/ * AllocSetContextCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Anum_pg_rewrite_ev_action ; 
 int /*<<< orphan*/  Anum_pg_rewrite_ev_class ; 
 int /*<<< orphan*/  Anum_pg_rewrite_ev_qual ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CacheMemoryContext ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ MemoryContextAlloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MemoryContextCopyAndSetIdentifier (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * MemoryContextSwitchTo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetDescr (TYPE_4__*) ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_4__*) ; 
 int /*<<< orphan*/  RelationGetRelid (TYPE_4__*) ; 
 int /*<<< orphan*/  RewriteRelRulenameIndexId ; 
 int /*<<< orphan*/  RewriteRelationId ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* TextDatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_getattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 scalar_t__ repalloc (TYPE_3__**,int) ; 
 int /*<<< orphan*/  setRuleCheckAsUser (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ stringToNode (char*) ; 
 int /*<<< orphan*/  systable_beginscan (TYPE_4__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
RelationBuildRuleLock(Relation relation)
{
	MemoryContext rulescxt;
	MemoryContext oldcxt;
	HeapTuple	rewrite_tuple;
	Relation	rewrite_desc;
	TupleDesc	rewrite_tupdesc;
	SysScanDesc rewrite_scan;
	ScanKeyData key;
	RuleLock   *rulelock;
	int			numlocks;
	RewriteRule **rules;
	int			maxlocks;

	/*
	 * Make the private context.  Assume it'll not contain much data.
	 */
	rulescxt = AllocSetContextCreate(CacheMemoryContext,
									 "relation rules",
									 ALLOCSET_SMALL_SIZES);
	relation->rd_rulescxt = rulescxt;
	MemoryContextCopyAndSetIdentifier(rulescxt,
									  RelationGetRelationName(relation));

	/*
	 * allocate an array to hold the rewrite rules (the array is extended if
	 * necessary)
	 */
	maxlocks = 4;
	rules = (RewriteRule **)
		MemoryContextAlloc(rulescxt, sizeof(RewriteRule *) * maxlocks);
	numlocks = 0;

	/*
	 * form a scan key
	 */
	ScanKeyInit(&key,
				Anum_pg_rewrite_ev_class,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(RelationGetRelid(relation)));

	/*
	 * open pg_rewrite and begin a scan
	 *
	 * Note: since we scan the rules using RewriteRelRulenameIndexId, we will
	 * be reading the rules in name order, except possibly during
	 * emergency-recovery operations (ie, IgnoreSystemIndexes). This in turn
	 * ensures that rules will be fired in name order.
	 */
	rewrite_desc = table_open(RewriteRelationId, AccessShareLock);
	rewrite_tupdesc = RelationGetDescr(rewrite_desc);
	rewrite_scan = systable_beginscan(rewrite_desc,
									  RewriteRelRulenameIndexId,
									  true, NULL,
									  1, &key);

	while (HeapTupleIsValid(rewrite_tuple = systable_getnext(rewrite_scan)))
	{
		Form_pg_rewrite rewrite_form = (Form_pg_rewrite) GETSTRUCT(rewrite_tuple);
		bool		isnull;
		Datum		rule_datum;
		char	   *rule_str;
		RewriteRule *rule;

		rule = (RewriteRule *) MemoryContextAlloc(rulescxt,
												  sizeof(RewriteRule));

		rule->ruleId = rewrite_form->oid;

		rule->event = rewrite_form->ev_type - '0';
		rule->enabled = rewrite_form->ev_enabled;
		rule->isInstead = rewrite_form->is_instead;

		/*
		 * Must use heap_getattr to fetch ev_action and ev_qual.  Also, the
		 * rule strings are often large enough to be toasted.  To avoid
		 * leaking memory in the caller's context, do the detoasting here so
		 * we can free the detoasted version.
		 */
		rule_datum = heap_getattr(rewrite_tuple,
								  Anum_pg_rewrite_ev_action,
								  rewrite_tupdesc,
								  &isnull);
		Assert(!isnull);
		rule_str = TextDatumGetCString(rule_datum);
		oldcxt = MemoryContextSwitchTo(rulescxt);
		rule->actions = (List *) stringToNode(rule_str);
		MemoryContextSwitchTo(oldcxt);
		pfree(rule_str);

		rule_datum = heap_getattr(rewrite_tuple,
								  Anum_pg_rewrite_ev_qual,
								  rewrite_tupdesc,
								  &isnull);
		Assert(!isnull);
		rule_str = TextDatumGetCString(rule_datum);
		oldcxt = MemoryContextSwitchTo(rulescxt);
		rule->qual = (Node *) stringToNode(rule_str);
		MemoryContextSwitchTo(oldcxt);
		pfree(rule_str);

		/*
		 * We want the rule's table references to be checked as though by the
		 * table owner, not the user referencing the rule.  Therefore, scan
		 * through the rule's actions and set the checkAsUser field on all
		 * rtable entries.  We have to look at the qual as well, in case it
		 * contains sublinks.
		 *
		 * The reason for doing this when the rule is loaded, rather than when
		 * it is stored, is that otherwise ALTER TABLE OWNER would have to
		 * grovel through stored rules to update checkAsUser fields. Scanning
		 * the rule tree during load is relatively cheap (compared to
		 * constructing it in the first place), so we do it here.
		 */
		setRuleCheckAsUser((Node *) rule->actions, relation->rd_rel->relowner);
		setRuleCheckAsUser(rule->qual, relation->rd_rel->relowner);

		if (numlocks >= maxlocks)
		{
			maxlocks *= 2;
			rules = (RewriteRule **)
				repalloc(rules, sizeof(RewriteRule *) * maxlocks);
		}
		rules[numlocks++] = rule;
	}

	/*
	 * end the scan and close the attribute relation
	 */
	systable_endscan(rewrite_scan);
	table_close(rewrite_desc, AccessShareLock);

	/*
	 * there might not be any rules (if relhasrules is out-of-date)
	 */
	if (numlocks == 0)
	{
		relation->rd_rules = NULL;
		relation->rd_rulescxt = NULL;
		MemoryContextDelete(rulescxt);
		return;
	}

	/*
	 * form a RuleLock and insert into relation
	 */
	rulelock = (RuleLock *) MemoryContextAlloc(rulescxt, sizeof(RuleLock));
	rulelock->numLocks = numlocks;
	rulelock->rules = rules;

	relation->rd_rules = rulelock;
}