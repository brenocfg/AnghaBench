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
struct nfsd4_cb_sec {int flavor; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
#define  RPC_AUTH_NULL 129 
#define  RPC_AUTH_UNIX 128 
 int /*<<< orphan*/  nfs_ok ; 
 int /*<<< orphan*/  nfserr_encr_alg_unsupp ; 

__attribute__((used)) static __be32 nfsd4_check_cb_sec(struct nfsd4_cb_sec *cbs)
{
	switch (cbs->flavor) {
	case RPC_AUTH_NULL:
	case RPC_AUTH_UNIX:
		return nfs_ok;
	default:
		/*
		 * GSS case: the spec doesn't allow us to return this
		 * error.  But it also doesn't allow us not to support
		 * GSS.
		 * I'd rather this fail hard than return some error the
		 * client might think it can already handle:
		 */
		return nfserr_encr_alg_unsupp;
	}
}