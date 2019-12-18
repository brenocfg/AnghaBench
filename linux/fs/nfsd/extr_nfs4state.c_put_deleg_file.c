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
struct nfs4_file {scalar_t__ fi_delegees; int /*<<< orphan*/  fi_lock; int /*<<< orphan*/  fi_deleg_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfsd_file_put (struct nfsd_file*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swap (struct nfsd_file*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void put_deleg_file(struct nfs4_file *fp)
{
	struct nfsd_file *nf = NULL;

	spin_lock(&fp->fi_lock);
	if (--fp->fi_delegees == 0)
		swap(nf, fp->fi_deleg_file);
	spin_unlock(&fp->fi_lock);

	if (nf)
		nfsd_file_put(nf);
}