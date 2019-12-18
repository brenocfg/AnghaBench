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
struct net {int dummy; } ;
struct file {int /*<<< orphan*/  f_cred; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SIMPLE_TRANSACTION_LIMIT ; 
 int get_int (char**,int*) ; 
 struct net* netns (struct file*) ; 
 int nfsd_nrthreads (struct net*) ; 
 int nfsd_svc (int,struct net*,int /*<<< orphan*/ ) ; 
 int scnprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ssize_t write_threads(struct file *file, char *buf, size_t size)
{
	char *mesg = buf;
	int rv;
	struct net *net = netns(file);

	if (size > 0) {
		int newthreads;
		rv = get_int(&mesg, &newthreads);
		if (rv)
			return rv;
		if (newthreads < 0)
			return -EINVAL;
		rv = nfsd_svc(newthreads, net, file->f_cred);
		if (rv < 0)
			return rv;
	} else
		rv = nfsd_nrthreads(net);

	return scnprintf(buf, SIMPLE_TRANSACTION_LIMIT, "%d\n", rv);
}