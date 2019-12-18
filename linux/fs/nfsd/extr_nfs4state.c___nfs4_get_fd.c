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
struct nfs4_file {scalar_t__* fi_fds; } ;

/* Variables and functions */
 struct nfsd_file* nfsd_file_get (scalar_t__) ; 

__attribute__((used)) static struct nfsd_file *
__nfs4_get_fd(struct nfs4_file *f, int oflag)
{
	if (f->fi_fds[oflag])
		return nfsd_file_get(f->fi_fds[oflag]);
	return NULL;
}