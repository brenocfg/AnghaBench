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
struct nfsd4_open {scalar_t__ op_claim_type; } ;

/* Variables and functions */
 scalar_t__ NFS4_OPEN_CLAIM_DELEGATE_CUR ; 
 scalar_t__ NFS4_OPEN_CLAIM_DELEG_CUR_FH ; 

__attribute__((used)) static bool nfsd4_is_deleg_cur(struct nfsd4_open *open)
{
	return open->op_claim_type == NFS4_OPEN_CLAIM_DELEGATE_CUR ||
	       open->op_claim_type == NFS4_OPEN_CLAIM_DELEG_CUR_FH;
}