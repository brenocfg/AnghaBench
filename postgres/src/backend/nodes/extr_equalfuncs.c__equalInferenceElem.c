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
typedef  int /*<<< orphan*/  InferenceElem ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expr ; 
 int /*<<< orphan*/  infercollid ; 
 int /*<<< orphan*/  inferopclass ; 

__attribute__((used)) static bool
_equalInferenceElem(const InferenceElem *a, const InferenceElem *b)
{
	COMPARE_NODE_FIELD(expr);
	COMPARE_SCALAR_FIELD(infercollid);
	COMPARE_SCALAR_FIELD(inferopclass);

	return true;
}