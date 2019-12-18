#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct nfs_open_dir_context {scalar_t__ attr_gencount; int duped; scalar_t__ dup_cookie; } ;
struct nfs_inode {scalar_t__ attr_gencount; } ;
struct nfs_cache_array {int size; scalar_t__ eof_index; scalar_t__ last_cookie; TYPE_2__* array; } ;
struct TYPE_11__ {scalar_t__* dir_cookie; scalar_t__ current_index; int cache_entry_index; int eof; TYPE_3__* ctx; TYPE_5__* file; } ;
typedef  TYPE_4__ nfs_readdir_descriptor_t ;
typedef  scalar_t__ loff_t ;
struct TYPE_12__ {struct nfs_open_dir_context* private_data; } ;
struct TYPE_10__ {scalar_t__ pos; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;
struct TYPE_9__ {scalar_t__ cookie; TYPE_1__ string; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBADCOOKIE ; 
 int ELOOP ; 
 struct nfs_inode* NFS_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_inode (TYPE_5__*) ; 
 int /*<<< orphan*/  nfs_readdir_inode_mapping_valid (struct nfs_inode*) ; 
 int /*<<< orphan*/  pr_notice (char*,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ printk_ratelimit () ; 

__attribute__((used)) static
int nfs_readdir_search_for_cookie(struct nfs_cache_array *array, nfs_readdir_descriptor_t *desc)
{
	int i;
	loff_t new_pos;
	int status = -EAGAIN;

	for (i = 0; i < array->size; i++) {
		if (array->array[i].cookie == *desc->dir_cookie) {
			struct nfs_inode *nfsi = NFS_I(file_inode(desc->file));
			struct nfs_open_dir_context *ctx = desc->file->private_data;

			new_pos = desc->current_index + i;
			if (ctx->attr_gencount != nfsi->attr_gencount ||
			    !nfs_readdir_inode_mapping_valid(nfsi)) {
				ctx->duped = 0;
				ctx->attr_gencount = nfsi->attr_gencount;
			} else if (new_pos < desc->ctx->pos) {
				if (ctx->duped > 0
				    && ctx->dup_cookie == *desc->dir_cookie) {
					if (printk_ratelimit()) {
						pr_notice("NFS: directory %pD2 contains a readdir loop."
								"Please contact your server vendor.  "
								"The file: %.*s has duplicate cookie %llu\n",
								desc->file, array->array[i].string.len,
								array->array[i].string.name, *desc->dir_cookie);
					}
					status = -ELOOP;
					goto out;
				}
				ctx->dup_cookie = *desc->dir_cookie;
				ctx->duped = -1;
			}
			desc->ctx->pos = new_pos;
			desc->cache_entry_index = i;
			return 0;
		}
	}
	if (array->eof_index >= 0) {
		status = -EBADCOOKIE;
		if (*desc->dir_cookie == array->last_cookie)
			desc->eof = true;
	}
out:
	return status;
}