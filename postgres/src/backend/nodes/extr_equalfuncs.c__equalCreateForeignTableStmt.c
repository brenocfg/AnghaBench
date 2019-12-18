#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ CreateForeignTableStmt ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _equalCreateStmt (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  options ; 
 int /*<<< orphan*/  servername ; 

__attribute__((used)) static bool
_equalCreateForeignTableStmt(const CreateForeignTableStmt *a, const CreateForeignTableStmt *b)
{
	if (!_equalCreateStmt(&a->base, &b->base))
		return false;

	COMPARE_STRING_FIELD(servername);
	COMPARE_NODE_FIELD(options);

	return true;
}