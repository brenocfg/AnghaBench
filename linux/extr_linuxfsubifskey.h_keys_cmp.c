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
union ubifs_key {scalar_t__* u32; } ;
struct ubifs_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int keys_cmp(const struct ubifs_info *c,
			   const union ubifs_key *key1,
			   const union ubifs_key *key2)
{
	if (key1->u32[0] < key2->u32[0])
		return -1;
	if (key1->u32[0] > key2->u32[0])
		return 1;
	if (key1->u32[1] < key2->u32[1])
		return -1;
	if (key1->u32[1] > key2->u32[1])
		return 1;

	return 0;
}