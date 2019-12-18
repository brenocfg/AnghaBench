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
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  CurrentOfExpr ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_INT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  WRITE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_UINT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cursor_name ; 
 int /*<<< orphan*/  cursor_param ; 
 int /*<<< orphan*/  cvarno ; 

__attribute__((used)) static void
_outCurrentOfExpr(StringInfo str, const CurrentOfExpr *node)
{
	WRITE_NODE_TYPE("CURRENTOFEXPR");

	WRITE_UINT_FIELD(cvarno);
	WRITE_STRING_FIELD(cursor_name);
	WRITE_INT_FIELD(cursor_param);
}