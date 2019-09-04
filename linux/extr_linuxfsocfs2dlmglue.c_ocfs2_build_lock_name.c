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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  enum ocfs2_lock_type { ____Placeholder_ocfs2_lock_type } ocfs2_lock_type ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int OCFS2_LOCK_ID_MAX_LEN ; 
 int /*<<< orphan*/  OCFS2_LOCK_ID_PAD ; 
 int OCFS2_NUM_LOCK_TYPES ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,char*) ; 
 int ocfs2_lock_type_char (int) ; 
 int snprintf (char*,int,char*,int,int /*<<< orphan*/ ,long long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ocfs2_build_lock_name(enum ocfs2_lock_type type,
				  u64 blkno,
				  u32 generation,
				  char *name)
{
	int len;

	BUG_ON(type >= OCFS2_NUM_LOCK_TYPES);

	len = snprintf(name, OCFS2_LOCK_ID_MAX_LEN, "%c%s%016llx%08x",
		       ocfs2_lock_type_char(type), OCFS2_LOCK_ID_PAD,
		       (long long)blkno, generation);

	BUG_ON(len != (OCFS2_LOCK_ID_MAX_LEN - 1));

	mlog(0, "built lock resource with name: %s\n", name);
}