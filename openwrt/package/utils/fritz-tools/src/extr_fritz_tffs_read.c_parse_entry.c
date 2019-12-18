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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint32_t ;
struct tffs_entry_header {int dummy; } ;
struct tffs_entry {int /*<<< orphan*/ * val; struct tffs_entry_header* header; } ;

/* Variables and functions */

__attribute__((used)) static void parse_entry(uint8_t *buffer, uint32_t pos,
			struct tffs_entry *entry)
{
	entry->header = (struct tffs_entry_header *) &buffer[pos];
	entry->val = &buffer[pos + sizeof(struct tffs_entry_header)];
}