#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct nfs_open_dir_context {int duped; } ;
struct TYPE_6__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct nfs_cache_array_entry {scalar_t__ cookie; int /*<<< orphan*/  d_type; int /*<<< orphan*/  ino; TYPE_1__ string; } ;
struct nfs_cache_array {int size; scalar_t__ eof_index; scalar_t__ last_cookie; struct nfs_cache_array_entry* array; } ;
struct file {struct nfs_open_dir_context* private_data; } ;
struct TYPE_7__ {int cache_entry_index; int eof; scalar_t__* dir_cookie; int /*<<< orphan*/  page; TYPE_4__* ctx; struct file* file; } ;
typedef  TYPE_2__ nfs_readdir_descriptor_t ;
struct TYPE_8__ {int /*<<< orphan*/  pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIRCACHE ; 
 int /*<<< orphan*/  cache_page_release (TYPE_2__*) ; 
 int /*<<< orphan*/  dfprintk (int /*<<< orphan*/ ,char*,unsigned long long,int) ; 
 int /*<<< orphan*/  dir_emit (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nfs_cache_array* kmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_compat_user_ino64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static 
int nfs_do_filldir(nfs_readdir_descriptor_t *desc)
{
	struct file	*file = desc->file;
	int i = 0;
	int res = 0;
	struct nfs_cache_array *array = NULL;
	struct nfs_open_dir_context *ctx = file->private_data;

	array = kmap(desc->page);
	for (i = desc->cache_entry_index; i < array->size; i++) {
		struct nfs_cache_array_entry *ent;

		ent = &array->array[i];
		if (!dir_emit(desc->ctx, ent->string.name, ent->string.len,
		    nfs_compat_user_ino64(ent->ino), ent->d_type)) {
			desc->eof = true;
			break;
		}
		desc->ctx->pos++;
		if (i < (array->size-1))
			*desc->dir_cookie = array->array[i+1].cookie;
		else
			*desc->dir_cookie = array->last_cookie;
		if (ctx->duped != 0)
			ctx->duped = 1;
	}
	if (array->eof_index >= 0)
		desc->eof = true;

	kunmap(desc->page);
	cache_page_release(desc);
	dfprintk(DIRCACHE, "NFS: nfs_do_filldir() filling ended @ cookie %Lu; returning = %d\n",
			(unsigned long long)*desc->dir_cookie, res);
	return res;
}