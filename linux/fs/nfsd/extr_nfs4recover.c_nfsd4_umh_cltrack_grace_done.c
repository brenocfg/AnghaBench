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
struct nfsd_net {int /*<<< orphan*/  boot_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (char*) ; 
 char* nfsd4_cltrack_legacy_topdir () ; 
 int /*<<< orphan*/  nfsd4_umh_cltrack_upcall (char*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nfsd4_umh_cltrack_grace_done(struct nfsd_net *nn)
{
	char *legacy;
	char timestr[22]; /* FIXME: better way to determine max size? */

	sprintf(timestr, "%ld", nn->boot_time);
	legacy = nfsd4_cltrack_legacy_topdir();
	nfsd4_umh_cltrack_upcall("gracedone", timestr, legacy, NULL);
	kfree(legacy);
}