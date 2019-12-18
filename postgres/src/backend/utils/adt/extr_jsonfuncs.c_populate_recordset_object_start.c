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
typedef  int /*<<< orphan*/  ctl ;
struct TYPE_8__ {int entrysize; int /*<<< orphan*/  hcxt; int /*<<< orphan*/  keysize; } ;
struct TYPE_7__ {int /*<<< orphan*/  json_hash; int /*<<< orphan*/  function_name; TYPE_1__* lex; } ;
struct TYPE_6__ {int lex_level; } ;
typedef  TYPE_2__ PopulateRecordsetState ;
typedef  int /*<<< orphan*/  JsonHashEntry ;
typedef  TYPE_3__ HASHCTL ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 int HASH_CONTEXT ; 
 int HASH_ELEM ; 
 int /*<<< orphan*/  NAMEDATALEN ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_create (char*,int,TYPE_3__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
populate_recordset_object_start(void *state)
{
	PopulateRecordsetState *_state = (PopulateRecordsetState *) state;
	int			lex_level = _state->lex->lex_level;
	HASHCTL		ctl;

	/* Reject object at top level: we must have an array at level 0 */
	if (lex_level == 0)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("cannot call %s on an object",
						_state->function_name)));

	/* Nested objects require no special processing */
	if (lex_level > 1)
		return;

	/* Object at level 1: set up a new hash table for this object */
	memset(&ctl, 0, sizeof(ctl));
	ctl.keysize = NAMEDATALEN;
	ctl.entrysize = sizeof(JsonHashEntry);
	ctl.hcxt = CurrentMemoryContext;
	_state->json_hash = hash_create("json object hashtable",
									100,
									&ctl,
									HASH_ELEM | HASH_CONTEXT);
}