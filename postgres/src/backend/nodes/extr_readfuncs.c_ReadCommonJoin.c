#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  plan; } ;
typedef  TYPE_1__ Join ;

/* Variables and functions */
 int /*<<< orphan*/  JoinType ; 
 int /*<<< orphan*/  READ_BOOL_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ_ENUM_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ_TEMP_LOCALS () ; 
 int /*<<< orphan*/  ReadCommonPlan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inner_unique ; 
 int /*<<< orphan*/  joinqual ; 
 int /*<<< orphan*/  jointype ; 

__attribute__((used)) static void
ReadCommonJoin(Join *local_node)
{
	READ_TEMP_LOCALS();

	ReadCommonPlan(&local_node->plan);

	READ_ENUM_FIELD(jointype, JoinType);
	READ_BOOL_FIELD(inner_unique);
	READ_NODE_FIELD(joinqual);
}