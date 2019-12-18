#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  data; } ;
struct TYPE_10__ {TYPE_1__ binary; } ;
struct TYPE_11__ {scalar_t__ type; TYPE_2__ val; } ;
typedef  TYPE_3__ JsonbValue ;
typedef  int /*<<< orphan*/  JsonbParseState ;
typedef  scalar_t__ JsonbIteratorToken ;
typedef  int /*<<< orphan*/  JsonbIterator ;

/* Variables and functions */
 int /*<<< orphan*/ * JsonbIteratorInit (int /*<<< orphan*/ ) ; 
 scalar_t__ JsonbIteratorNext (int /*<<< orphan*/ **,TYPE_3__*,int) ; 
 scalar_t__ WJB_BEGIN_ARRAY ; 
 scalar_t__ WJB_DONE ; 
 scalar_t__ WJB_ELEM ; 
 scalar_t__ WJB_VALUE ; 
 scalar_t__ jbvBinary ; 
 TYPE_3__* pushJsonbValueScalar (int /*<<< orphan*/ **,scalar_t__,TYPE_3__*) ; 

JsonbValue *
pushJsonbValue(JsonbParseState **pstate, JsonbIteratorToken seq,
			   JsonbValue *jbval)
{
	JsonbIterator *it;
	JsonbValue *res = NULL;
	JsonbValue	v;
	JsonbIteratorToken tok;

	if (!jbval || (seq != WJB_ELEM && seq != WJB_VALUE) ||
		jbval->type != jbvBinary)
	{
		/* drop through */
		return pushJsonbValueScalar(pstate, seq, jbval);
	}

	/* unpack the binary and add each piece to the pstate */
	it = JsonbIteratorInit(jbval->val.binary.data);
	while ((tok = JsonbIteratorNext(&it, &v, false)) != WJB_DONE)
		res = pushJsonbValueScalar(pstate, tok,
								   tok < WJB_BEGIN_ARRAY ? &v : NULL);

	return res;
}