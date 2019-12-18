#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  jsonb_cont; int /*<<< orphan*/  json_hash; } ;
struct TYPE_15__ {TYPE_2__ val; scalar_t__ is_json; } ;
struct TYPE_10__ {scalar_t__ type; int len; int /*<<< orphan*/ * str; } ;
struct TYPE_12__ {int /*<<< orphan*/ * jsonb; TYPE_1__ json; } ;
struct TYPE_14__ {TYPE_3__ val; scalar_t__ is_json; } ;
struct TYPE_13__ {scalar_t__ type; int /*<<< orphan*/ * val; } ;
typedef  TYPE_4__ JsonHashEntry ;
typedef  TYPE_5__ JsValue ;
typedef  TYPE_6__ JsObject ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_FIND ; 
 scalar_t__ JSON_TOKEN_NULL ; 
 int /*<<< orphan*/ * getKeyJsonValueFromContainer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_4__* hash_search (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static bool
JsObjectGetField(JsObject *obj, char *field, JsValue *jsv)
{
	jsv->is_json = obj->is_json;

	if (jsv->is_json)
	{
		JsonHashEntry *hashentry = hash_search(obj->val.json_hash, field,
											   HASH_FIND, NULL);

		jsv->val.json.type = hashentry ? hashentry->type : JSON_TOKEN_NULL;
		jsv->val.json.str = jsv->val.json.type == JSON_TOKEN_NULL ? NULL :
			hashentry->val;
		jsv->val.json.len = jsv->val.json.str ? -1 : 0; /* null-terminated */

		return hashentry != NULL;
	}
	else
	{
		jsv->val.jsonb = !obj->val.jsonb_cont ? NULL :
			getKeyJsonValueFromContainer(obj->val.jsonb_cont, field, strlen(field),
										 NULL);

		return jsv->val.jsonb != NULL;
	}
}