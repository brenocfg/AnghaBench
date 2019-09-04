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
struct pnv_php_slot {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnv_php_free_slot ; 

__attribute__((used)) static inline void pnv_php_put_slot(struct pnv_php_slot *php_slot)
{

	if (!php_slot)
		return;

	kref_put(&php_slot->kref, pnv_php_free_slot);
}