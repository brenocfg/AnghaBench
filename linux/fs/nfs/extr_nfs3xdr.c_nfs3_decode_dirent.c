#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct xdr_stream {int dummy; } ;
struct user_namespace {int dummy; } ;
struct nfs_entry {int eof; scalar_t__ ino; int /*<<< orphan*/  cookie; int /*<<< orphan*/  prev_cookie; int /*<<< orphan*/  fh; TYPE_2__* fattr; int /*<<< orphan*/  d_type; int /*<<< orphan*/  len; int /*<<< orphan*/  name; TYPE_1__* server; } ;
typedef  scalar_t__ __be32 ;
struct TYPE_4__ {int valid; scalar_t__ fileid; scalar_t__ mounted_on_fileid; int /*<<< orphan*/  mode; } ;
struct TYPE_3__ {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  DT_UNKNOWN ; 
 int E2BIG ; 
 int EAGAIN ; 
 int EBADCOOKIE ; 
 int NFS_ATTR_FATTR_MOUNTED_ON_FILEID ; 
 int NFS_ATTR_FATTR_V3 ; 
 int decode_cookie3 (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int decode_fileid3 (struct xdr_stream*,scalar_t__*) ; 
 int decode_inline_filename3 (struct xdr_stream*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int decode_nfs_fh3 (struct xdr_stream*,int /*<<< orphan*/ ) ; 
 int decode_post_op_attr (struct xdr_stream*,TYPE_2__*,struct user_namespace*) ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  nfs_umode_to_dtype (int /*<<< orphan*/ ) ; 
 struct user_namespace* rpc_userns (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__* xdr_inline_decode (struct xdr_stream*,int) ; 
 scalar_t__ xdr_zero ; 
 int /*<<< orphan*/  zero_nfs_fh3 (int /*<<< orphan*/ ) ; 

int nfs3_decode_dirent(struct xdr_stream *xdr, struct nfs_entry *entry,
		       bool plus)
{
	struct user_namespace *userns = rpc_userns(entry->server->client);
	struct nfs_entry old = *entry;
	__be32 *p;
	int error;
	u64 new_cookie;

	p = xdr_inline_decode(xdr, 4);
	if (unlikely(!p))
		return -EAGAIN;
	if (*p == xdr_zero) {
		p = xdr_inline_decode(xdr, 4);
		if (unlikely(!p))
			return -EAGAIN;
		if (*p == xdr_zero)
			return -EAGAIN;
		entry->eof = 1;
		return -EBADCOOKIE;
	}

	error = decode_fileid3(xdr, &entry->ino);
	if (unlikely(error))
		return error;

	error = decode_inline_filename3(xdr, &entry->name, &entry->len);
	if (unlikely(error))
		return error;

	error = decode_cookie3(xdr, &new_cookie);
	if (unlikely(error))
		return error;

	entry->d_type = DT_UNKNOWN;

	if (plus) {
		entry->fattr->valid = 0;
		error = decode_post_op_attr(xdr, entry->fattr, userns);
		if (unlikely(error))
			return error;
		if (entry->fattr->valid & NFS_ATTR_FATTR_V3)
			entry->d_type = nfs_umode_to_dtype(entry->fattr->mode);

		if (entry->fattr->fileid != entry->ino) {
			entry->fattr->mounted_on_fileid = entry->ino;
			entry->fattr->valid |= NFS_ATTR_FATTR_MOUNTED_ON_FILEID;
		}

		/* In fact, a post_op_fh3: */
		p = xdr_inline_decode(xdr, 4);
		if (unlikely(!p))
			return -EAGAIN;
		if (*p != xdr_zero) {
			error = decode_nfs_fh3(xdr, entry->fh);
			if (unlikely(error)) {
				if (error == -E2BIG)
					goto out_truncated;
				return error;
			}
		} else
			zero_nfs_fh3(entry->fh);
	}

	entry->prev_cookie = entry->cookie;
	entry->cookie = new_cookie;

	return 0;

out_truncated:
	dprintk("NFS: directory entry contains invalid file handle\n");
	*entry = old;
	return -EAGAIN;
}