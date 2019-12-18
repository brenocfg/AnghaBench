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
typedef  int /*<<< orphan*/  ObjectWithArgs ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  args_unspecified ; 
 int /*<<< orphan*/  objargs ; 
 int /*<<< orphan*/  objname ; 

__attribute__((used)) static bool
_equalObjectWithArgs(const ObjectWithArgs *a, const ObjectWithArgs *b)
{
	COMPARE_NODE_FIELD(objname);
	COMPARE_NODE_FIELD(objargs);
	COMPARE_SCALAR_FIELD(args_unspecified);

	return true;
}