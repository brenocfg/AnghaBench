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
struct TYPE_7__ {int /*<<< orphan*/  len; int /*<<< orphan*/  val; } ;
struct TYPE_8__ {TYPE_1__ string; } ;
struct TYPE_9__ {TYPE_2__ val; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  SV ;
typedef  TYPE_3__ JsonbValue ;
typedef  int /*<<< orphan*/  JsonbParseState ;
typedef  int /*<<< orphan*/  I32 ;
typedef  int /*<<< orphan*/  HV ;

/* Variables and functions */
 int /*<<< orphan*/  SV_to_JsonbValue (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  WJB_BEGIN_OBJECT ; 
 int /*<<< orphan*/  WJB_END_OBJECT ; 
 int /*<<< orphan*/  WJB_KEY ; 
 int /*<<< orphan*/  dTHX ; 
 int /*<<< orphan*/  hv_iterinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hv_iternextsv (int /*<<< orphan*/ *,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jbvString ; 
 int /*<<< orphan*/  pnstrdup (char*,int /*<<< orphan*/ ) ; 
 TYPE_3__* pushJsonbValue (int /*<<< orphan*/ **,int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static JsonbValue *
HV_to_JsonbValue(HV *obj, JsonbParseState **jsonb_state)
{
	dTHX;
	JsonbValue	key;
	SV		   *val;
	char	   *kstr;
	I32			klen;

	key.type = jbvString;

	pushJsonbValue(jsonb_state, WJB_BEGIN_OBJECT, NULL);

	(void) hv_iterinit(obj);

	while ((val = hv_iternextsv(obj, &kstr, &klen)))
	{
		key.val.string.val = pnstrdup(kstr, klen);
		key.val.string.len = klen;
		pushJsonbValue(jsonb_state, WJB_KEY, &key);
		(void) SV_to_JsonbValue(val, jsonb_state, false);
	}

	return pushJsonbValue(jsonb_state, WJB_END_OBJECT, NULL);
}