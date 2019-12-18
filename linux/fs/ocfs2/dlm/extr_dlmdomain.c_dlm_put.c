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
struct dlm_ctxt {int /*<<< orphan*/  dlm_refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  dlm_ctxt_release ; 
 int /*<<< orphan*/  dlm_domain_lock ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void dlm_put(struct dlm_ctxt *dlm)
{
	spin_lock(&dlm_domain_lock);
	kref_put(&dlm->dlm_refs, dlm_ctxt_release);
	spin_unlock(&dlm_domain_lock);
}