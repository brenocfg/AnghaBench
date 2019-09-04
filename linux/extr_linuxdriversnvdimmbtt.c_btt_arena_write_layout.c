#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
struct nd_gen_sb {int dummy; } ;
struct nd_btt {int /*<<< orphan*/  const* uuid; TYPE_1__* ndns; } ;
struct btt_sb {void* checksum; void* flags; void* info2off; void* logoff; void* mapoff; void* dataoff; void* nextoff; void* infosize; void* nfree; void* internal_nlba; void* internal_lbasize; void* external_nlba; void* external_lbasize; void* version_minor; void* version_major; int /*<<< orphan*/  parent_uuid; int /*<<< orphan*/  uuid; int /*<<< orphan*/  signature; } ;
struct arena_info {int flags; int external_lbasize; int external_nlba; int internal_lbasize; int internal_nlba; int nfree; scalar_t__ infooff; scalar_t__ info2off; scalar_t__ logoff; scalar_t__ mapoff; scalar_t__ dataoff; scalar_t__ nextoff; int /*<<< orphan*/  version_minor; int /*<<< orphan*/  version_major; struct nd_btt* nd_btt; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTT_SIG ; 
 int /*<<< orphan*/  BTT_SIG_LEN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int btt_info_write (struct arena_info*,struct btt_sb*) ; 
 int btt_log_init (struct arena_info*) ; 
 int btt_map_init (struct arena_info*) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int) ; 
 void* cpu_to_le64 (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct btt_sb*) ; 
 struct btt_sb* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ * nd_dev_to_uuid (int /*<<< orphan*/ *) ; 
 scalar_t__ nd_sb_checksum (struct nd_gen_sb*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int btt_arena_write_layout(struct arena_info *arena)
{
	int ret;
	u64 sum;
	struct btt_sb *super;
	struct nd_btt *nd_btt = arena->nd_btt;
	const u8 *parent_uuid = nd_dev_to_uuid(&nd_btt->ndns->dev);

	ret = btt_map_init(arena);
	if (ret)
		return ret;

	ret = btt_log_init(arena);
	if (ret)
		return ret;

	super = kzalloc(sizeof(struct btt_sb), GFP_NOIO);
	if (!super)
		return -ENOMEM;

	strncpy(super->signature, BTT_SIG, BTT_SIG_LEN);
	memcpy(super->uuid, nd_btt->uuid, 16);
	memcpy(super->parent_uuid, parent_uuid, 16);
	super->flags = cpu_to_le32(arena->flags);
	super->version_major = cpu_to_le16(arena->version_major);
	super->version_minor = cpu_to_le16(arena->version_minor);
	super->external_lbasize = cpu_to_le32(arena->external_lbasize);
	super->external_nlba = cpu_to_le32(arena->external_nlba);
	super->internal_lbasize = cpu_to_le32(arena->internal_lbasize);
	super->internal_nlba = cpu_to_le32(arena->internal_nlba);
	super->nfree = cpu_to_le32(arena->nfree);
	super->infosize = cpu_to_le32(sizeof(struct btt_sb));
	super->nextoff = cpu_to_le64(arena->nextoff);
	/*
	 * Subtract arena->infooff (arena start) so numbers are relative
	 * to 'this' arena
	 */
	super->dataoff = cpu_to_le64(arena->dataoff - arena->infooff);
	super->mapoff = cpu_to_le64(arena->mapoff - arena->infooff);
	super->logoff = cpu_to_le64(arena->logoff - arena->infooff);
	super->info2off = cpu_to_le64(arena->info2off - arena->infooff);

	super->flags = 0;
	sum = nd_sb_checksum((struct nd_gen_sb *) super);
	super->checksum = cpu_to_le64(sum);

	ret = btt_info_write(arena, super);

	kfree(super);
	return ret;
}