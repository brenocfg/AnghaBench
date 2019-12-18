#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * policy_name; } ;
typedef  TYPE_1__ RowSecurityPolicy ;
typedef  int /*<<< orphan*/  ListCell ;

/* Variables and functions */
 scalar_t__ lfirst (int /*<<< orphan*/  const*) ; 
 int strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
row_security_policy_cmp(const ListCell *a, const ListCell *b)
{
	const RowSecurityPolicy *pa = (const RowSecurityPolicy *) lfirst(a);
	const RowSecurityPolicy *pb = (const RowSecurityPolicy *) lfirst(b);

	/* Guard against NULL policy names from extensions */
	if (pa->policy_name == NULL)
		return pb->policy_name == NULL ? 0 : 1;
	if (pb->policy_name == NULL)
		return -1;

	return strcmp(pa->policy_name, pb->policy_name);
}