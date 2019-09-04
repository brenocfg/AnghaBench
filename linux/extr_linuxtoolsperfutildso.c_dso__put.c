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
struct dso {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  dso__delete (struct dso*) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 

void dso__put(struct dso *dso)
{
	if (dso && refcount_dec_and_test(&dso->refcnt))
		dso__delete(dso);
}