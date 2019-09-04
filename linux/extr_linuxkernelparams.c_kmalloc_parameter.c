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
struct kmalloced_param {void* val; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct kmalloced_param* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmalloced_params ; 
 int /*<<< orphan*/  kmalloced_params_lock ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *kmalloc_parameter(unsigned int size)
{
	struct kmalloced_param *p;

	p = kmalloc(sizeof(*p) + size, GFP_KERNEL);
	if (!p)
		return NULL;

	spin_lock(&kmalloced_params_lock);
	list_add(&p->list, &kmalloced_params);
	spin_unlock(&kmalloced_params_lock);

	return p->val;
}