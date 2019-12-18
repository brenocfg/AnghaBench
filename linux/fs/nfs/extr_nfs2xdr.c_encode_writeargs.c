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
typedef  int /*<<< orphan*/  u32 ;
struct xdr_stream {int dummy; } ;
struct nfs_pgio_args {int /*<<< orphan*/  pgbase; int /*<<< orphan*/  pages; int /*<<< orphan*/  fh; int /*<<< orphan*/  count; int /*<<< orphan*/  offset; } ;
typedef  void* __be32 ;

/* Variables and functions */
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_fhandle (struct xdr_stream*,int /*<<< orphan*/ ) ; 
 void** xdr_reserve_space (struct xdr_stream*,int) ; 
 int /*<<< orphan*/  xdr_write_pages (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void encode_writeargs(struct xdr_stream *xdr,
			     const struct nfs_pgio_args *args)
{
	u32 offset = args->offset;
	u32 count = args->count;
	__be32 *p;

	encode_fhandle(xdr, args->fh);

	p = xdr_reserve_space(xdr, 4 + 4 + 4 + 4);
	*p++ = cpu_to_be32(offset);
	*p++ = cpu_to_be32(offset);
	*p++ = cpu_to_be32(count);

	/* nfsdata */
	*p = cpu_to_be32(count);
	xdr_write_pages(xdr, args->pages, args->pgbase, count);
}