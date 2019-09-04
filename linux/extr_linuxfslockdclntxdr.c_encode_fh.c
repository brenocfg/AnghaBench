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
typedef  int /*<<< orphan*/  u8 ;
struct xdr_stream {int dummy; } ;
struct nfs_fh {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS2_FHSIZE ; 
 int /*<<< orphan*/  encode_netobj (struct xdr_stream*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void encode_fh(struct xdr_stream *xdr, const struct nfs_fh *fh)
{
	encode_netobj(xdr, (u8 *)&fh->data, NFS2_FHSIZE);
}