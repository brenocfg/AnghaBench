#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  cflags; scalar_t__ regex; } ;
struct TYPE_13__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  patternlen; int /*<<< orphan*/  pattern; } ;
struct TYPE_14__ {TYPE_1__ like_regex; } ;
struct TYPE_18__ {TYPE_2__ content; } ;
struct TYPE_15__ {int /*<<< orphan*/  len; int /*<<< orphan*/  val; } ;
struct TYPE_16__ {TYPE_3__ string; } ;
struct TYPE_17__ {TYPE_4__ val; } ;
typedef  TYPE_5__ JsonbValue ;
typedef  TYPE_6__ JsonPathItem ;
typedef  int /*<<< orphan*/  JsonPathBool ;
typedef  TYPE_7__ JsonLikeRegexContext ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_COLLATION_OID ; 
 scalar_t__ RE_compile_and_execute (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ cstring_to_text_with_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* getScalar (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jbvString ; 
 int /*<<< orphan*/  jpbFalse ; 
 int /*<<< orphan*/  jpbTrue ; 
 int /*<<< orphan*/  jpbUnknown ; 
 int /*<<< orphan*/  jspConvertRegexFlags (int /*<<< orphan*/ ) ; 

__attribute__((used)) static JsonPathBool
executeLikeRegex(JsonPathItem *jsp, JsonbValue *str, JsonbValue *rarg,
				 void *param)
{
	JsonLikeRegexContext *cxt = param;

	if (!(str = getScalar(str, jbvString)))
		return jpbUnknown;

	/* Cache regex text and converted flags. */
	if (!cxt->regex)
	{
		cxt->regex =
			cstring_to_text_with_len(jsp->content.like_regex.pattern,
									 jsp->content.like_regex.patternlen);
		cxt->cflags = jspConvertRegexFlags(jsp->content.like_regex.flags);
	}

	if (RE_compile_and_execute(cxt->regex, str->val.string.val,
							   str->val.string.len,
							   cxt->cflags, DEFAULT_COLLATION_OID, 0, NULL))
		return jpbTrue;

	return jpbFalse;
}