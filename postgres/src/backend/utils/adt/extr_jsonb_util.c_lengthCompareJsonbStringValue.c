#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  len; int /*<<< orphan*/  val; } ;
struct TYPE_5__ {TYPE_1__ string; } ;
struct TYPE_6__ {scalar_t__ type; TYPE_2__ val; } ;
typedef  TYPE_3__ JsonbValue ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ jbvString ; 
 int lengthCompareJsonbString (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lengthCompareJsonbStringValue(const void *a, const void *b)
{
	const JsonbValue *va = (const JsonbValue *) a;
	const JsonbValue *vb = (const JsonbValue *) b;

	Assert(va->type == jbvString);
	Assert(vb->type == jbvString);

	return lengthCompareJsonbString(va->val.string.val, va->val.string.len,
									vb->val.string.val, vb->val.string.len);
}