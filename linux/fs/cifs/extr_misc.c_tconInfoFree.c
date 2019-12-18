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
struct TYPE_2__ {struct cifs_tcon* fid; } ;
struct cifs_tcon {struct cifs_tcon* dfs_path; TYPE_1__ crfid; int /*<<< orphan*/  password; struct cifs_tcon* nativeFileSystem; } ;

/* Variables and functions */
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (struct cifs_tcon*) ; 
 int /*<<< orphan*/  kzfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tconInfoAllocCount ; 

void
tconInfoFree(struct cifs_tcon *buf_to_free)
{
	if (buf_to_free == NULL) {
		cifs_dbg(FYI, "Null buffer passed to tconInfoFree\n");
		return;
	}
	atomic_dec(&tconInfoAllocCount);
	kfree(buf_to_free->nativeFileSystem);
	kzfree(buf_to_free->password);
	kfree(buf_to_free->crfid.fid);
#ifdef CONFIG_CIFS_DFS_UPCALL
	kfree(buf_to_free->dfs_path);
#endif
	kfree(buf_to_free);
}