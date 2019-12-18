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
struct nfsd_net {int /*<<< orphan*/  boot_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfsd_reset_boot_verifier_locked (struct nfsd_net*) ; 
 int /*<<< orphan*/  write_seqlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_sequnlock (int /*<<< orphan*/ *) ; 

void nfsd_reset_boot_verifier(struct nfsd_net *nn)
{
	write_seqlock(&nn->boot_lock);
	nfsd_reset_boot_verifier_locked(nn);
	write_sequnlock(&nn->boot_lock);
}