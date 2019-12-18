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
typedef  int /*<<< orphan*/  ctl ;
struct TYPE_9__ {int entrysize; int /*<<< orphan*/  hcxt; int /*<<< orphan*/  keysize; } ;
struct TYPE_8__ {char const* function_name; int /*<<< orphan*/ * lex; int /*<<< orphan*/ * hash; } ;
struct TYPE_7__ {int /*<<< orphan*/  object_field_end; int /*<<< orphan*/  object_field_start; int /*<<< orphan*/  scalar; int /*<<< orphan*/  array_start; void* semstate; } ;
typedef  TYPE_1__ JsonSemAction ;
typedef  int /*<<< orphan*/  JsonLexContext ;
typedef  int /*<<< orphan*/  JsonHashEntry ;
typedef  TYPE_2__ JHashState ;
typedef  int /*<<< orphan*/  HTAB ;
typedef  TYPE_3__ HASHCTL ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int HASH_CONTEXT ; 
 int HASH_ELEM ; 
 int /*<<< orphan*/  NAMEDATALEN ; 
 int /*<<< orphan*/  hash_array_start ; 
 int /*<<< orphan*/ * hash_create (char*,int,TYPE_3__*,int) ; 
 int /*<<< orphan*/  hash_object_field_end ; 
 int /*<<< orphan*/  hash_object_field_start ; 
 int /*<<< orphan*/  hash_scalar ; 
 int /*<<< orphan*/ * makeJsonLexContextCstringLen (char*,int,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 void* palloc0 (int) ; 
 int /*<<< orphan*/  pg_parse_json (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static HTAB *
get_json_object_as_hash(char *json, int len, const char *funcname)
{
	HASHCTL		ctl;
	HTAB	   *tab;
	JHashState *state;
	JsonLexContext *lex = makeJsonLexContextCstringLen(json, len, true);
	JsonSemAction *sem;

	memset(&ctl, 0, sizeof(ctl));
	ctl.keysize = NAMEDATALEN;
	ctl.entrysize = sizeof(JsonHashEntry);
	ctl.hcxt = CurrentMemoryContext;
	tab = hash_create("json object hashtable",
					  100,
					  &ctl,
					  HASH_ELEM | HASH_CONTEXT);

	state = palloc0(sizeof(JHashState));
	sem = palloc0(sizeof(JsonSemAction));

	state->function_name = funcname;
	state->hash = tab;
	state->lex = lex;

	sem->semstate = (void *) state;
	sem->array_start = hash_array_start;
	sem->scalar = hash_scalar;
	sem->object_field_start = hash_object_field_start;
	sem->object_field_end = hash_object_field_end;

	pg_parse_json(lex, sem);

	return tab;
}