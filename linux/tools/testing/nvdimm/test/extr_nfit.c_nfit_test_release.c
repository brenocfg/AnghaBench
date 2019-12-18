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
struct nfit_test {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nfit_test*) ; 
 struct nfit_test* to_nfit_test (struct device*) ; 

__attribute__((used)) static void nfit_test_release(struct device *dev)
{
	struct nfit_test *nfit_test = to_nfit_test(dev);

	kfree(nfit_test);
}