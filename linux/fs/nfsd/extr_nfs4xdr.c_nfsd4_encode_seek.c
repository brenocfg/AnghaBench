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
struct nfsd4_seek {int /*<<< orphan*/  seek_pos; int /*<<< orphan*/  seek_eof; } ;
struct nfsd4_compoundres {int /*<<< orphan*/  xdr; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_encode_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_reserve_space (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static __be32
nfsd4_encode_seek(struct nfsd4_compoundres *resp, __be32 nfserr,
		  struct nfsd4_seek *seek)
{
	__be32 *p;

	p = xdr_reserve_space(&resp->xdr, 4 + 8);
	*p++ = cpu_to_be32(seek->seek_eof);
	p = xdr_encode_hyper(p, seek->seek_pos);

	return 0;
}