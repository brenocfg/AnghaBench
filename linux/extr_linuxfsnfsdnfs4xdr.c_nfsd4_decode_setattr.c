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
struct nfsd4_setattr {int /*<<< orphan*/  sa_label; int /*<<< orphan*/  sa_acl; int /*<<< orphan*/  sa_iattr; int /*<<< orphan*/  sa_bmval; int /*<<< orphan*/  sa_stateid; } ;
struct nfsd4_compoundargs {int dummy; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 scalar_t__ nfsd4_decode_fattr (struct nfsd4_compoundargs*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ nfsd4_decode_stateid (struct nfsd4_compoundargs*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __be32
nfsd4_decode_setattr(struct nfsd4_compoundargs *argp, struct nfsd4_setattr *setattr)
{
	__be32 status;

	status = nfsd4_decode_stateid(argp, &setattr->sa_stateid);
	if (status)
		return status;
	return nfsd4_decode_fattr(argp, setattr->sa_bmval, &setattr->sa_iattr,
				  &setattr->sa_acl, &setattr->sa_label, NULL);
}