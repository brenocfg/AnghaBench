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
typedef  int /*<<< orphan*/  Plan ;
typedef  int /*<<< orphan*/  Join ;

/* Variables and functions */
 int /*<<< orphan*/  COPY_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COPY_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CopyPlanFields (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inner_unique ; 
 int /*<<< orphan*/  joinqual ; 
 int /*<<< orphan*/  jointype ; 

__attribute__((used)) static void
CopyJoinFields(const Join *from, Join *newnode)
{
	CopyPlanFields((const Plan *) from, (Plan *) newnode);

	COPY_SCALAR_FIELD(jointype);
	COPY_SCALAR_FIELD(inner_unique);
	COPY_NODE_FIELD(joinqual);
}