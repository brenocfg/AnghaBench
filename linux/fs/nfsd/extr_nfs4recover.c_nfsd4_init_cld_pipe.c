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

/* Variables and functions */
 int __nfsd4_init_cld_pipe (struct net*) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static int
nfsd4_init_cld_pipe(struct net *net)
{
	int status;

	status = __nfsd4_init_cld_pipe(net);
	if (!status)
		printk("NFSD: Using old nfsdcld client tracking operations.\n");
	return status;
}