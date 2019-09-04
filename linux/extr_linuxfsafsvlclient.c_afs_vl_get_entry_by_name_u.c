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
struct key {int dummy; } ;
struct afs_vldb_entry {int dummy; } ;
struct afs_uvldbentry__xdr {int dummy; } ;
struct afs_net {int dummy; } ;
struct afs_call {int ret_reply0; int /*<<< orphan*/ * request; struct afs_vldb_entry** reply; struct key* key; } ;
struct afs_addr_cursor {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct afs_vldb_entry* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int VLGETENTRYBYNAMEU ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  afs_RXVLGetEntryByNameU ; 
 struct afs_call* afs_alloc_flat_call (struct afs_net*,int /*<<< orphan*/ *,size_t,int) ; 
 scalar_t__ afs_make_call (struct afs_addr_cursor*,struct afs_call*,int /*<<< orphan*/ ,int) ; 
 void* htonl (int) ; 
 int /*<<< orphan*/  kfree (struct afs_vldb_entry*) ; 
 struct afs_vldb_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  trace_afs_make_vl_call (struct afs_call*) ; 

struct afs_vldb_entry *afs_vl_get_entry_by_name_u(struct afs_net *net,
						  struct afs_addr_cursor *ac,
						  struct key *key,
						  const char *volname,
						  int volnamesz)
{
	struct afs_vldb_entry *entry;
	struct afs_call *call;
	size_t reqsz, padsz;
	__be32 *bp;

	_enter("");

	padsz = (4 - (volnamesz & 3)) & 3;
	reqsz = 8 + volnamesz + padsz;

	entry = kzalloc(sizeof(struct afs_vldb_entry), GFP_KERNEL);
	if (!entry)
		return ERR_PTR(-ENOMEM);

	call = afs_alloc_flat_call(net, &afs_RXVLGetEntryByNameU, reqsz,
				   sizeof(struct afs_uvldbentry__xdr));
	if (!call) {
		kfree(entry);
		return ERR_PTR(-ENOMEM);
	}

	call->key = key;
	call->reply[0] = entry;
	call->ret_reply0 = true;

	/* Marshall the parameters */
	bp = call->request;
	*bp++ = htonl(VLGETENTRYBYNAMEU);
	*bp++ = htonl(volnamesz);
	memcpy(bp, volname, volnamesz);
	if (padsz > 0)
		memset((void *)bp + volnamesz, 0, padsz);

	trace_afs_make_vl_call(call);
	return (struct afs_vldb_entry *)afs_make_call(ac, call, GFP_KERNEL, false);
}