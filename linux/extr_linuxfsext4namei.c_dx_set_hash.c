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
struct dx_entry {int /*<<< orphan*/  hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (unsigned int) ; 

__attribute__((used)) static inline void dx_set_hash(struct dx_entry *entry, unsigned value)
{
	entry->hash = cpu_to_le32(value);
}