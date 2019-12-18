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
typedef  int /*<<< orphan*/  CreatePublicationStmt ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  for_all_tables ; 
 int /*<<< orphan*/  options ; 
 int /*<<< orphan*/  pubname ; 
 int /*<<< orphan*/  tables ; 

__attribute__((used)) static bool
_equalCreatePublicationStmt(const CreatePublicationStmt *a,
							const CreatePublicationStmt *b)
{
	COMPARE_STRING_FIELD(pubname);
	COMPARE_NODE_FIELD(options);
	COMPARE_NODE_FIELD(tables);
	COMPARE_SCALAR_FIELD(for_all_tables);

	return true;
}