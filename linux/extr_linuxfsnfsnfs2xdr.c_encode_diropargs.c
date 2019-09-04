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
struct nfs_fh {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  encode_fhandle (struct xdr_stream*,struct nfs_fh const*) ; 
 int /*<<< orphan*/  encode_filename (struct xdr_stream*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void encode_diropargs(struct xdr_stream *xdr, const struct nfs_fh *fh,
			     const char *name, u32 length)
{
	encode_fhandle(xdr, fh);
	encode_filename(xdr, name, length);
}