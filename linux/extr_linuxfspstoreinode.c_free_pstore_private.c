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
struct pstore_private {struct pstore_private* record; struct pstore_private* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct pstore_private*) ; 

__attribute__((used)) static void free_pstore_private(struct pstore_private *private)
{
	if (!private)
		return;
	if (private->record) {
		kfree(private->record->buf);
		kfree(private->record);
	}
	kfree(private);
}