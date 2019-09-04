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
struct nfs4_file {int dummy; } ;
struct knfsd_fh {int dummy; } ;

/* Variables and functions */
 unsigned int file_hashval (struct knfsd_fh*) ; 
 struct nfs4_file* find_file_locked (struct knfsd_fh*,unsigned int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

struct nfs4_file *
find_file(struct knfsd_fh *fh)
{
	struct nfs4_file *fp;
	unsigned int hashval = file_hashval(fh);

	rcu_read_lock();
	fp = find_file_locked(fh, hashval);
	rcu_read_unlock();
	return fp;
}