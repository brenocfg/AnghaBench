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
struct acm {int /*<<< orphan*/  minor; } ;

/* Variables and functions */
 int /*<<< orphan*/  acm_minors ; 
 int /*<<< orphan*/  acm_minors_lock ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void acm_release_minor(struct acm *acm)
{
	mutex_lock(&acm_minors_lock);
	idr_remove(&acm_minors, acm->minor);
	mutex_unlock(&acm_minors_lock);
}