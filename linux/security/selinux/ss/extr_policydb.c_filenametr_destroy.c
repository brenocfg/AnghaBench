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
struct filename_trans {void* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  kfree (void*) ; 

__attribute__((used)) static int filenametr_destroy(void *key, void *datum, void *p)
{
	struct filename_trans *ft = key;

	kfree(ft->name);
	kfree(key);
	kfree(datum);
	cond_resched();
	return 0;
}