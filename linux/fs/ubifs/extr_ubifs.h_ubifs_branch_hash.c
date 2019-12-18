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
typedef  void u8 ;
struct ubifs_info {int key_len; } ;
struct ubifs_branch {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline u8 *ubifs_branch_hash(struct ubifs_info *c,
				    struct ubifs_branch *br)
{
	return (void *)br + sizeof(*br) + c->key_len;
}