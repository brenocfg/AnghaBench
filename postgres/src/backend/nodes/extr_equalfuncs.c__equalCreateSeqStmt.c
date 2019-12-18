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
typedef  int /*<<< orphan*/  CreateSeqStmt ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  for_identity ; 
 int /*<<< orphan*/  if_not_exists ; 
 int /*<<< orphan*/  options ; 
 int /*<<< orphan*/  ownerId ; 
 int /*<<< orphan*/  sequence ; 

__attribute__((used)) static bool
_equalCreateSeqStmt(const CreateSeqStmt *a, const CreateSeqStmt *b)
{
	COMPARE_NODE_FIELD(sequence);
	COMPARE_NODE_FIELD(options);
	COMPARE_SCALAR_FIELD(ownerId);
	COMPARE_SCALAR_FIELD(for_identity);
	COMPARE_SCALAR_FIELD(if_not_exists);

	return true;
}