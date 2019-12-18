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
typedef  union ubifs_key {int dummy; } ubifs_key ;
struct ubifs_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ keys_cmp (struct ubifs_info*,union ubifs_key*,union ubifs_key*) ; 

__attribute__((used)) static int key_in_range(struct ubifs_info *c, union ubifs_key *key,
			union ubifs_key *from_key, union ubifs_key *to_key)
{
	if (keys_cmp(c, key, from_key) < 0)
		return 0;
	if (keys_cmp(c, key, to_key) > 0)
		return 0;
	return 1;
}