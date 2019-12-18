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
struct nfsd_net {int /*<<< orphan*/  nfssvc_boot; } ;

/* Variables and functions */
 int /*<<< orphan*/  ktime_get_real_ts64 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfsd_reset_boot_verifier_locked(struct nfsd_net *nn)
{
	ktime_get_real_ts64(&nn->nfssvc_boot);
}