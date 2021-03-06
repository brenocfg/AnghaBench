#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xdr_stream {int dummy; } ;
struct nfs_seqid {TYPE_1__* sequence; } ;
struct TYPE_2__ {int /*<<< orphan*/  counter; } ;

/* Variables and functions */
 int /*<<< orphan*/  encode_uint32 (struct xdr_stream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void encode_nfs4_seqid(struct xdr_stream *xdr,
		const struct nfs_seqid *seqid)
{
	if (seqid != NULL)
		encode_uint32(xdr, seqid->sequence->counter);
	else
		encode_uint32(xdr, 0);
}