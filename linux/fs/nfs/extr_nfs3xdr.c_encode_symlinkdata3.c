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
struct user_namespace {int dummy; } ;
struct nfs3_symlinkargs {int /*<<< orphan*/  pathlen; int /*<<< orphan*/  pages; int /*<<< orphan*/  sattr; } ;

/* Variables and functions */
 int /*<<< orphan*/  encode_nfspath3 (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_sattr3 (struct xdr_stream*,int /*<<< orphan*/ ,struct user_namespace*) ; 

__attribute__((used)) static void encode_symlinkdata3(struct xdr_stream *xdr,
				const void *data,
				struct user_namespace *userns)
{
	const struct nfs3_symlinkargs *args = data;

	encode_sattr3(xdr, args->sattr, userns);
	encode_nfspath3(xdr, args->pages, args->pathlen);
}