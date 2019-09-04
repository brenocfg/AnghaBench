#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xdr_stream {int dummy; } ;
struct xdr_buf {int dummy; } ;
struct page {int dummy; } ;
struct nfs_entry {scalar_t__ eof; } ;
struct nfs_cache_array {int /*<<< orphan*/  size; int /*<<< orphan*/  eof_index; } ;
struct TYPE_4__ {int /*<<< orphan*/  file; scalar_t__ plus; } ;
typedef  TYPE_1__ nfs_readdir_descriptor_t ;

/* Variables and functions */
 int EAGAIN ; 
 int EBADCOOKIE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_dentry (int /*<<< orphan*/ ) ; 
 struct nfs_cache_array* kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  nfs_prime_dcache (int /*<<< orphan*/ ,struct nfs_entry*) ; 
 int nfs_readdir_add_to_array (struct nfs_entry*,struct page*) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int xdr_decode (TYPE_1__*,struct nfs_entry*,struct xdr_stream*) ; 
 int /*<<< orphan*/  xdr_init_decode_pages (struct xdr_stream*,struct xdr_buf*,struct page**,unsigned int) ; 
 int /*<<< orphan*/  xdr_set_scratch_buffer (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
int nfs_readdir_page_filler(nfs_readdir_descriptor_t *desc, struct nfs_entry *entry,
				struct page **xdr_pages, struct page *page, unsigned int buflen)
{
	struct xdr_stream stream;
	struct xdr_buf buf;
	struct page *scratch;
	struct nfs_cache_array *array;
	unsigned int count = 0;
	int status;

	scratch = alloc_page(GFP_KERNEL);
	if (scratch == NULL)
		return -ENOMEM;

	if (buflen == 0)
		goto out_nopages;

	xdr_init_decode_pages(&stream, &buf, xdr_pages, buflen);
	xdr_set_scratch_buffer(&stream, page_address(scratch), PAGE_SIZE);

	do {
		status = xdr_decode(desc, entry, &stream);
		if (status != 0) {
			if (status == -EAGAIN)
				status = 0;
			break;
		}

		count++;

		if (desc->plus)
			nfs_prime_dcache(file_dentry(desc->file), entry);

		status = nfs_readdir_add_to_array(entry, page);
		if (status != 0)
			break;
	} while (!entry->eof);

out_nopages:
	if (count == 0 || (status == -EBADCOOKIE && entry->eof != 0)) {
		array = kmap(page);
		array->eof_index = array->size;
		status = 0;
		kunmap(page);
	}

	put_page(scratch);
	return status;
}