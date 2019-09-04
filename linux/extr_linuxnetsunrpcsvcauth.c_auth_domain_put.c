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
struct auth_domain {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  auth_domain_lock ; 
 int /*<<< orphan*/  auth_domain_release ; 
 int /*<<< orphan*/  kref_put_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void auth_domain_put(struct auth_domain *dom)
{
	kref_put_lock(&dom->ref, auth_domain_release, &auth_domain_lock);
}