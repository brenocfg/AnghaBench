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
struct idr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int idr_alloc (struct idr*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_destroy (struct idr*) ; 
 char* idr_find (struct idr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_for_each_entry (struct idr*,void*,int) ; 
 int /*<<< orphan*/  idr_is_empty (struct idr*) ; 
 int /*<<< orphan*/  idr_remove (struct idr*,int) ; 
 int /*<<< orphan*/  idr_replace (struct idr*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void idr_align_test(struct idr *idr)
{
	char name[] = "Motorola 68000";
	int i, id;
	void *entry;

	for (i = 0; i < 9; i++) {
		BUG_ON(idr_alloc(idr, &name[i], 0, 0, GFP_KERNEL) != i);
		idr_for_each_entry(idr, entry, id);
	}
	idr_destroy(idr);

	for (i = 1; i < 10; i++) {
		BUG_ON(idr_alloc(idr, &name[i], 0, 0, GFP_KERNEL) != i - 1);
		idr_for_each_entry(idr, entry, id);
	}
	idr_destroy(idr);

	for (i = 2; i < 11; i++) {
		BUG_ON(idr_alloc(idr, &name[i], 0, 0, GFP_KERNEL) != i - 2);
		idr_for_each_entry(idr, entry, id);
	}
	idr_destroy(idr);

	for (i = 3; i < 12; i++) {
		BUG_ON(idr_alloc(idr, &name[i], 0, 0, GFP_KERNEL) != i - 3);
		idr_for_each_entry(idr, entry, id);
	}
	idr_destroy(idr);

	for (i = 0; i < 8; i++) {
		BUG_ON(idr_alloc(idr, &name[i], 0, 0, GFP_KERNEL) != 0);
		BUG_ON(idr_alloc(idr, &name[i + 1], 0, 0, GFP_KERNEL) != 1);
		idr_for_each_entry(idr, entry, id);
		idr_remove(idr, 1);
		idr_for_each_entry(idr, entry, id);
		idr_remove(idr, 0);
		BUG_ON(!idr_is_empty(idr));
	}

	for (i = 0; i < 8; i++) {
		BUG_ON(idr_alloc(idr, NULL, 0, 0, GFP_KERNEL) != 0);
		idr_for_each_entry(idr, entry, id);
		idr_replace(idr, &name[i], 0);
		idr_for_each_entry(idr, entry, id);
		BUG_ON(idr_find(idr, 0) != &name[i]);
		idr_remove(idr, 0);
	}

	for (i = 0; i < 8; i++) {
		BUG_ON(idr_alloc(idr, &name[i], 0, 0, GFP_KERNEL) != 0);
		BUG_ON(idr_alloc(idr, NULL, 0, 0, GFP_KERNEL) != 1);
		idr_remove(idr, 1);
		idr_for_each_entry(idr, entry, id);
		idr_replace(idr, &name[i + 1], 0);
		idr_for_each_entry(idr, entry, id);
		idr_remove(idr, 0);
	}
}