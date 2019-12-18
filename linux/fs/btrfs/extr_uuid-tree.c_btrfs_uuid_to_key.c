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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct btrfs_key {void* offset; void* objectid; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 void* get_unaligned_le64 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void btrfs_uuid_to_key(u8 *uuid, u8 type, struct btrfs_key *key)
{
	key->type = type;
	key->objectid = get_unaligned_le64(uuid);
	key->offset = get_unaligned_le64(uuid + sizeof(u64));
}