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
struct qstr {scalar_t__ len; scalar_t__ name; } ;
struct page {unsigned int file_type; int /*<<< orphan*/  nid; } ;
struct inode {int /*<<< orphan*/  i_size; } ;
struct erofs_qstr {scalar_t__ end; scalar_t__ name; } ;
struct erofs_dirent {unsigned int file_type; int /*<<< orphan*/  nid; } ;
typedef  int /*<<< orphan*/  erofs_nid_t ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  EROFS_BLKSIZ ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int PTR_ERR (struct page*) ; 
 int PTR_ERR_OR_ZERO (struct page*) ; 
 struct page* find_target_block_classic (struct inode*,struct erofs_qstr*,int*) ; 
 struct page* find_target_dirent (struct erofs_qstr*,void*,int /*<<< orphan*/ ,int) ; 
 void* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 

int erofs_namei(struct inode *dir,
		struct qstr *name,
		erofs_nid_t *nid, unsigned int *d_type)
{
	int ndirents;
	struct page *page;
	void *data;
	struct erofs_dirent *de;
	struct erofs_qstr qn;

	if (!dir->i_size)
		return -ENOENT;

	qn.name = name->name;
	qn.end = name->name + name->len;

	ndirents = 0;
	page = find_target_block_classic(dir, &qn, &ndirents);

	if (IS_ERR(page))
		return PTR_ERR(page);

	data = kmap_atomic(page);
	/* the target page has been mapped */
	if (ndirents)
		de = find_target_dirent(&qn, data, EROFS_BLKSIZ, ndirents);
	else
		de = (struct erofs_dirent *)data;

	if (!IS_ERR(de)) {
		*nid = le64_to_cpu(de->nid);
		*d_type = de->file_type;
	}

	kunmap_atomic(data);
	put_page(page);

	return PTR_ERR_OR_ZERO(de);
}