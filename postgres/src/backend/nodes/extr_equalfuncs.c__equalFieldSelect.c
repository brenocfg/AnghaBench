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
typedef  int /*<<< orphan*/  FieldSelect ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arg ; 
 int /*<<< orphan*/  fieldnum ; 
 int /*<<< orphan*/  resultcollid ; 
 int /*<<< orphan*/  resulttype ; 
 int /*<<< orphan*/  resulttypmod ; 

__attribute__((used)) static bool
_equalFieldSelect(const FieldSelect *a, const FieldSelect *b)
{
	COMPARE_NODE_FIELD(arg);
	COMPARE_SCALAR_FIELD(fieldnum);
	COMPARE_SCALAR_FIELD(resulttype);
	COMPARE_SCALAR_FIELD(resulttypmod);
	COMPARE_SCALAR_FIELD(resultcollid);

	return true;
}