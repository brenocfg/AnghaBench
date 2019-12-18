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
struct nfs42_falloc_args {int /*<<< orphan*/  falloc_length; int /*<<< orphan*/  falloc_offset; int /*<<< orphan*/  falloc_stateid; } ;

/* Variables and functions */
 int /*<<< orphan*/  encode_nfs4_stateid (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  encode_uint64 (struct xdr_stream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void encode_fallocate(struct xdr_stream *xdr,
			     const struct nfs42_falloc_args *args)
{
	encode_nfs4_stateid(xdr, &args->falloc_stateid);
	encode_uint64(xdr, args->falloc_offset);
	encode_uint64(xdr, args->falloc_length);
}