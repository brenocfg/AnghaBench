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
typedef  int /*<<< orphan*/  FieldStore ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arg ; 
 int /*<<< orphan*/  fieldnums ; 
 int /*<<< orphan*/  newvals ; 
 int /*<<< orphan*/  resulttype ; 

__attribute__((used)) static bool
_equalFieldStore(const FieldStore *a, const FieldStore *b)
{
	COMPARE_NODE_FIELD(arg);
	COMPARE_NODE_FIELD(newvals);
	COMPARE_NODE_FIELD(fieldnums);
	COMPARE_SCALAR_FIELD(resulttype);

	return true;
}