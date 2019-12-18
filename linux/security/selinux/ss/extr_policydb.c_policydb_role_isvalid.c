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
struct TYPE_2__ {unsigned int nprim; } ;
struct policydb {TYPE_1__ p_roles; } ;

/* Variables and functions */

int policydb_role_isvalid(struct policydb *p, unsigned int role)
{
	if (!role || role > p->p_roles.nprim)
		return 0;
	return 1;
}