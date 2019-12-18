#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  useTz; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  JsonbValue ;
typedef  TYPE_1__ JsonPathItem ;
typedef  TYPE_2__ JsonPathExecContext ;
typedef  int /*<<< orphan*/  JsonPathBool ;

/* Variables and functions */
 int /*<<< orphan*/  compareItems (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static JsonPathBool
executeComparison(JsonPathItem *cmp, JsonbValue *lv, JsonbValue *rv, void *p)
{
	JsonPathExecContext *cxt = (JsonPathExecContext *) p;

	return compareItems(cmp->type, lv, rv, cxt->useTz);
}