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
typedef  int u32 ;
struct nfs4_file {int /*<<< orphan*/ * fi_access; int /*<<< orphan*/  fi_lock; } ;

/* Variables and functions */
 int NFS4_SHARE_ACCESS_READ ; 
 int NFS4_SHARE_ACCESS_WRITE ; 
 size_t O_RDONLY ; 
 size_t O_WRONLY ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
__nfs4_file_get_access(struct nfs4_file *fp, u32 access)
{
	lockdep_assert_held(&fp->fi_lock);

	if (access & NFS4_SHARE_ACCESS_WRITE)
		atomic_inc(&fp->fi_access[O_WRONLY]);
	if (access & NFS4_SHARE_ACCESS_READ)
		atomic_inc(&fp->fi_access[O_RDONLY]);
}