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
struct nfs4_layoutreturn_args {int dummy; } ;
struct compound_hdr {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void
encode_layoutreturn(struct xdr_stream *xdr,
		    const struct nfs4_layoutreturn_args *args,
		    struct compound_hdr *hdr)
{
}