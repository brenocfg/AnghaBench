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
typedef  int /*<<< orphan*/  ino_t ;

/* Variables and functions */
 int /*<<< orphan*/  UBIFS_S_KEY_BLOCK_MASK ; 
 int /*<<< orphan*/  data_key_init (struct ubifs_info const*,union ubifs_key*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void highest_data_key(const struct ubifs_info *c,
				   union ubifs_key *key, ino_t inum)
{
	data_key_init(c, key, inum, UBIFS_S_KEY_BLOCK_MASK);
}