#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ len; int /*<<< orphan*/  val; } ;
struct TYPE_8__ {TYPE_2__ string; } ;
struct TYPE_10__ {TYPE_1__ val; } ;
typedef  TYPE_3__ JsonbValue ;
typedef  int /*<<< orphan*/  JsonPathItem ;
typedef  int /*<<< orphan*/  JsonPathBool ;

/* Variables and functions */
 TYPE_3__* getScalar (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jbvString ; 
 int /*<<< orphan*/  jpbFalse ; 
 int /*<<< orphan*/  jpbTrue ; 
 int /*<<< orphan*/  jpbUnknown ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static JsonPathBool
executeStartsWith(JsonPathItem *jsp, JsonbValue *whole, JsonbValue *initial,
				  void *param)
{
	if (!(whole = getScalar(whole, jbvString)))
		return jpbUnknown;		/* error */

	if (!(initial = getScalar(initial, jbvString)))
		return jpbUnknown;		/* error */

	if (whole->val.string.len >= initial->val.string.len &&
		!memcmp(whole->val.string.val,
				initial->val.string.val,
				initial->val.string.len))
		return jpbTrue;

	return jpbFalse;
}