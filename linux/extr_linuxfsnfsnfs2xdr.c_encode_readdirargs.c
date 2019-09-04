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
struct nfs_readdirargs {int /*<<< orphan*/  count; int /*<<< orphan*/  cookie; int /*<<< orphan*/  fh; } ;
typedef  void* __be32 ;

/* Variables and functions */
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_fhandle (struct xdr_stream*,int /*<<< orphan*/ ) ; 
 void** xdr_reserve_space (struct xdr_stream*,int) ; 

__attribute__((used)) static void encode_readdirargs(struct xdr_stream *xdr,
			       const struct nfs_readdirargs *args)
{
	__be32 *p;

	encode_fhandle(xdr, args->fh);

	p = xdr_reserve_space(xdr, 4 + 4);
	*p++ = cpu_to_be32(args->cookie);
	*p = cpu_to_be32(args->count);
}