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
struct dlm_lock_resource {int /*<<< orphan*/  refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  dlm_lockres_release ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void dlm_lockres_put(struct dlm_lock_resource *res)
{
	kref_put(&res->refs, dlm_lockres_release);
}