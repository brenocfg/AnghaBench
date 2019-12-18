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
struct nfs4_file {int /*<<< orphan*/  fi_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  O_RDWR ; 
 struct nfsd_file* __nfs4_get_fd (struct nfs4_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct nfsd_file *
find_readable_file_locked(struct nfs4_file *f)
{
	struct nfsd_file *ret;

	lockdep_assert_held(&f->fi_lock);

	ret = __nfs4_get_fd(f, O_RDONLY);
	if (!ret)
		ret = __nfs4_get_fd(f, O_RDWR);
	return ret;
}