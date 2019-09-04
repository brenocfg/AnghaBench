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
typedef  int /*<<< orphan*/  uint64_t ;
struct xdr_stream {int dummy; } ;
struct nfsd4_exchange_id {int seqid; int flags; int spa_how; int /*<<< orphan*/ * spo_must_allow; int /*<<< orphan*/ * spo_must_enforce; int /*<<< orphan*/  clientid; } ;
struct nfsd4_compoundres {struct xdr_stream xdr; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {char* nodename; } ;

/* Variables and functions */
#define  SP4_MACH_CRED 129 
#define  SP4_NONE 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int XDR_QUADLEN (int) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  nfsd4_encode_bitmap (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfserr_resource ; 
 int strlen (char*) ; 
 TYPE_1__* utsname () ; 
 int /*<<< orphan*/ * xdr_encode_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_encode_opaque (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * xdr_encode_opaque_fixed (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * xdr_reserve_space (struct xdr_stream*,int) ; 

__attribute__((used)) static __be32
nfsd4_encode_exchange_id(struct nfsd4_compoundres *resp, __be32 nfserr,
			 struct nfsd4_exchange_id *exid)
{
	struct xdr_stream *xdr = &resp->xdr;
	__be32 *p;
	char *major_id;
	char *server_scope;
	int major_id_sz;
	int server_scope_sz;
	uint64_t minor_id = 0;

	major_id = utsname()->nodename;
	major_id_sz = strlen(major_id);
	server_scope = utsname()->nodename;
	server_scope_sz = strlen(server_scope);

	p = xdr_reserve_space(xdr,
		8 /* eir_clientid */ +
		4 /* eir_sequenceid */ +
		4 /* eir_flags */ +
		4 /* spr_how */);
	if (!p)
		return nfserr_resource;

	p = xdr_encode_opaque_fixed(p, &exid->clientid, 8);
	*p++ = cpu_to_be32(exid->seqid);
	*p++ = cpu_to_be32(exid->flags);

	*p++ = cpu_to_be32(exid->spa_how);

	switch (exid->spa_how) {
	case SP4_NONE:
		break;
	case SP4_MACH_CRED:
		/* spo_must_enforce bitmap: */
		nfserr = nfsd4_encode_bitmap(xdr,
					exid->spo_must_enforce[0],
					exid->spo_must_enforce[1],
					exid->spo_must_enforce[2]);
		if (nfserr)
			return nfserr;
		/* spo_must_allow bitmap: */
		nfserr = nfsd4_encode_bitmap(xdr,
					exid->spo_must_allow[0],
					exid->spo_must_allow[1],
					exid->spo_must_allow[2]);
		if (nfserr)
			return nfserr;
		break;
	default:
		WARN_ON_ONCE(1);
	}

	p = xdr_reserve_space(xdr,
		8 /* so_minor_id */ +
		4 /* so_major_id.len */ +
		(XDR_QUADLEN(major_id_sz) * 4) +
		4 /* eir_server_scope.len */ +
		(XDR_QUADLEN(server_scope_sz) * 4) +
		4 /* eir_server_impl_id.count (0) */);
	if (!p)
		return nfserr_resource;

	/* The server_owner struct */
	p = xdr_encode_hyper(p, minor_id);      /* Minor id */
	/* major id */
	p = xdr_encode_opaque(p, major_id, major_id_sz);

	/* Server scope */
	p = xdr_encode_opaque(p, server_scope, server_scope_sz);

	/* Implementation id */
	*p++ = cpu_to_be32(0);	/* zero length nfs_impl_id4 array */
	return 0;
}