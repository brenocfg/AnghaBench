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
struct nfsd_file {int dummy; } ;
struct nfs4_file {int /*<<< orphan*/  fi_lock; int /*<<< orphan*/ * fi_fds; int /*<<< orphan*/ * fi_access; } ;

/* Variables and functions */
 size_t O_RDWR ; 
 scalar_t__ atomic_dec_and_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  might_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsd_file_put (struct nfsd_file*) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swap (struct nfsd_file*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __nfs4_file_put_access(struct nfs4_file *fp, int oflag)
{
	might_lock(&fp->fi_lock);

	if (atomic_dec_and_lock(&fp->fi_access[oflag], &fp->fi_lock)) {
		struct nfsd_file *f1 = NULL;
		struct nfsd_file *f2 = NULL;

		swap(f1, fp->fi_fds[oflag]);
		if (atomic_read(&fp->fi_access[1 - oflag]) == 0)
			swap(f2, fp->fi_fds[O_RDWR]);
		spin_unlock(&fp->fi_lock);
		if (f1)
			nfsd_file_put(f1);
		if (f2)
			nfsd_file_put(f2);
	}
}