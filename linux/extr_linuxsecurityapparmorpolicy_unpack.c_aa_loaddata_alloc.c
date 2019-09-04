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
struct aa_loaddata {int /*<<< orphan*/  list; int /*<<< orphan*/  count; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct aa_loaddata* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct aa_loaddata*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvzalloc (size_t,int /*<<< orphan*/ ) ; 
 struct aa_loaddata* kzalloc (int,int /*<<< orphan*/ ) ; 

struct aa_loaddata *aa_loaddata_alloc(size_t size)
{
	struct aa_loaddata *d;

	d = kzalloc(sizeof(*d), GFP_KERNEL);
	if (d == NULL)
		return ERR_PTR(-ENOMEM);
	d->data = kvzalloc(size, GFP_KERNEL);
	if (!d->data) {
		kfree(d);
		return ERR_PTR(-ENOMEM);
	}
	kref_init(&d->count);
	INIT_LIST_HEAD(&d->list);

	return d;
}