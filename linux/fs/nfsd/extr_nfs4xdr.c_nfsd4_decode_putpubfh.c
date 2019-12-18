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
struct nfsd4_compoundargs {scalar_t__ minorversion; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  nfs_ok ; 
 int /*<<< orphan*/  nfserr_notsupp ; 

__attribute__((used)) static __be32
nfsd4_decode_putpubfh(struct nfsd4_compoundargs *argp, void *p)
{
	if (argp->minorversion == 0)
		return nfs_ok;
	return nfserr_notsupp;
}