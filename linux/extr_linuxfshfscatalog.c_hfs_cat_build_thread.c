#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct super_block {int dummy; } ;
struct qstr {int dummy; } ;
struct hfs_cat_thread {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  CName; int /*<<< orphan*/  ParID; int /*<<< orphan*/  reserved; } ;
struct TYPE_5__ {int type; TYPE_1__ thread; } ;
typedef  TYPE_2__ hfs_cat_rec ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfs_asc2mac (struct super_block*,int /*<<< orphan*/ *,struct qstr const*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hfs_cat_build_thread(struct super_block *sb,
				hfs_cat_rec *rec, int type,
				u32 parentid, const struct qstr *name)
{
	rec->type = type;
	memset(rec->thread.reserved, 0, sizeof(rec->thread.reserved));
	rec->thread.ParID = cpu_to_be32(parentid);
	hfs_asc2mac(sb, &rec->thread.CName, name);
	return sizeof(struct hfs_cat_thread);
}