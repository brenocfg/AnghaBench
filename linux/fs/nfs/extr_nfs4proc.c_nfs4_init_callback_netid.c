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
struct nfs_client {int /*<<< orphan*/  cl_ipaddr; } ;

/* Variables and functions */
 unsigned int scnprintf (char*,size_t,char*) ; 
 int /*<<< orphan*/ * strchr (int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static unsigned int
nfs4_init_callback_netid(const struct nfs_client *clp, char *buf, size_t len)
{
	if (strchr(clp->cl_ipaddr, ':') != NULL)
		return scnprintf(buf, len, "tcp6");
	else
		return scnprintf(buf, len, "tcp");
}