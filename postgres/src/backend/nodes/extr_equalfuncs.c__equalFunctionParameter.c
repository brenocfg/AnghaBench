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
typedef  int /*<<< orphan*/  FunctionParameter ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  argType ; 
 int /*<<< orphan*/  defexpr ; 
 int /*<<< orphan*/  mode ; 
 int /*<<< orphan*/  name ; 

__attribute__((used)) static bool
_equalFunctionParameter(const FunctionParameter *a, const FunctionParameter *b)
{
	COMPARE_STRING_FIELD(name);
	COMPARE_NODE_FIELD(argType);
	COMPARE_SCALAR_FIELD(mode);
	COMPARE_NODE_FIELD(defexpr);

	return true;
}