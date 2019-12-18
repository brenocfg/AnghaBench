#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * json_hash; } ;
struct TYPE_10__ {int is_json; TYPE_2__ val; } ;
struct TYPE_9__ {int /*<<< orphan*/ * json_hash; TYPE_1__* lex; } ;
struct TYPE_7__ {int lex_level; } ;
typedef  TYPE_3__ PopulateRecordsetState ;
typedef  TYPE_4__ JsObject ;

/* Variables and functions */
 int /*<<< orphan*/  hash_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  populate_recordset_record (TYPE_3__*,TYPE_4__*) ; 

__attribute__((used)) static void
populate_recordset_object_end(void *state)
{
	PopulateRecordsetState *_state = (PopulateRecordsetState *) state;
	JsObject	obj;

	/* Nested objects require no special processing */
	if (_state->lex->lex_level > 1)
		return;

	obj.is_json = true;
	obj.val.json_hash = _state->json_hash;

	/* Otherwise, construct and return a tuple based on this level-1 object */
	populate_recordset_record(_state, &obj);

	/* Done with hash for this object */
	hash_destroy(_state->json_hash);
	_state->json_hash = NULL;
}