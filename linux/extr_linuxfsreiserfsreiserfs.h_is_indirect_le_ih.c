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
struct item_head {int /*<<< orphan*/  ih_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  ih_version (struct item_head*) ; 
 int is_indirect_le_key (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int is_indirect_le_ih(struct item_head *ih)
{
	return is_indirect_le_key(ih_version(ih), &ih->ih_key);
}