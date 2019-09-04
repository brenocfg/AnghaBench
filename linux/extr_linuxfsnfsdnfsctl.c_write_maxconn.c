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
struct nfsd_net {unsigned int max_connections; } ;
struct file {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIMPLE_TRANSACTION_LIMIT ; 
 int get_uint (char**,unsigned int*) ; 
 struct nfsd_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netns (struct file*) ; 
 int /*<<< orphan*/  nfsd_net_id ; 
 int scnprintf (char*,int /*<<< orphan*/ ,char*,unsigned int) ; 

__attribute__((used)) static ssize_t write_maxconn(struct file *file, char *buf, size_t size)
{
	char *mesg = buf;
	struct nfsd_net *nn = net_generic(netns(file), nfsd_net_id);
	unsigned int maxconn = nn->max_connections;

	if (size > 0) {
		int rv = get_uint(&mesg, &maxconn);

		if (rv)
			return rv;
		nn->max_connections = maxconn;
	}

	return scnprintf(buf, SIMPLE_TRANSACTION_LIMIT, "%u\n", maxconn);
}