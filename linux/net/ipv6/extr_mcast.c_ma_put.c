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
struct ifmcaddr6 {int /*<<< orphan*/  idev; int /*<<< orphan*/  mca_refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  in6_dev_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ifmcaddr6*) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ma_put(struct ifmcaddr6 *mc)
{
	if (refcount_dec_and_test(&mc->mca_refcnt)) {
		in6_dev_put(mc->idev);
		kfree(mc);
	}
}