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
struct nfs4_cb_compound_hdr {int /*<<< orphan*/  nops; void** nops_p; int /*<<< orphan*/  ident; int /*<<< orphan*/  minorversion; } ;
typedef  void* __be32 ;

/* Variables and functions */
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 void** xdr_encode_empty_array (void**) ; 
 void** xdr_reserve_space (struct xdr_stream*,int) ; 

__attribute__((used)) static void encode_cb_compound4args(struct xdr_stream *xdr,
				    struct nfs4_cb_compound_hdr *hdr)
{
	__be32 * p;

	p = xdr_reserve_space(xdr, 4 + 4 + 4 + 4);
	p = xdr_encode_empty_array(p);		/* empty tag */
	*p++ = cpu_to_be32(hdr->minorversion);
	*p++ = cpu_to_be32(hdr->ident);

	hdr->nops_p = p;
	*p = cpu_to_be32(hdr->nops);		/* argarray element count */
}