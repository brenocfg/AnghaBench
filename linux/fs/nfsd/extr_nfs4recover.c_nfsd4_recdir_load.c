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
struct nfsd_net {int /*<<< orphan*/  rec_file; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  load_recdir ; 
 struct nfsd_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int nfsd4_list_rec_dir (int /*<<< orphan*/ ,struct nfsd_net*) ; 
 int /*<<< orphan*/  nfsd_net_id ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfsd4_recdir_load(struct net *net) {
	int status;
	struct nfsd_net *nn =  net_generic(net, nfsd_net_id);

	if (!nn->rec_file)
		return 0;

	status = nfsd4_list_rec_dir(load_recdir, nn);
	if (status)
		printk("nfsd4: failed loading clients from recovery"
			" directory %pD\n", nn->rec_file);
	return status;
}