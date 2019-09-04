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
struct xdr_stream {int dummy; } ;
struct nfs_openargs {int open_flags; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  NFS4_OPEN_CREATE ; 
 int /*<<< orphan*/  NFS4_OPEN_NOCREATE ; 
 int O_CREAT ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_createmode (struct xdr_stream*,struct nfs_openargs const*) ; 
 int /*<<< orphan*/ * reserve_space (struct xdr_stream*,int) ; 

__attribute__((used)) static void encode_opentype(struct xdr_stream *xdr, const struct nfs_openargs *arg)
{
	__be32 *p;

	p = reserve_space(xdr, 4);
	switch (arg->open_flags & O_CREAT) {
	case 0:
		*p = cpu_to_be32(NFS4_OPEN_NOCREATE);
		break;
	default:
		*p = cpu_to_be32(NFS4_OPEN_CREATE);
		encode_createmode(xdr, arg);
	}
}