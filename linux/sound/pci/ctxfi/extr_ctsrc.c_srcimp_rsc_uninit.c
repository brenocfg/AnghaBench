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
struct srcimp {int /*<<< orphan*/  rsc; int /*<<< orphan*/ * mgr; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * imappers; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rsc_uninit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int srcimp_rsc_uninit(struct srcimp *srcimp)
{
	kfree(srcimp->imappers);
	srcimp->imappers = NULL;
	srcimp->ops = NULL;
	srcimp->mgr = NULL;
	rsc_uninit(&srcimp->rsc);

	return 0;
}