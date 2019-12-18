#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  CurrentOfExpr ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cursor_name ; 
 int /*<<< orphan*/  cursor_param ; 
 int /*<<< orphan*/  cvarno ; 

__attribute__((used)) static bool
_equalCurrentOfExpr(const CurrentOfExpr *a, const CurrentOfExpr *b)
{
	COMPARE_SCALAR_FIELD(cvarno);
	COMPARE_STRING_FIELD(cursor_name);
	COMPARE_SCALAR_FIELD(cursor_param);

	return true;
}