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
typedef  int /*<<< orphan*/  u8 ;
struct page {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; struct address_space* i_mapping; } ;
struct erofs_qstr {int /*<<< orphan*/ * end; int /*<<< orphan*/ * name; } ;
struct erofs_dirent {int /*<<< orphan*/  nameoff; } ;
struct address_space {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  nid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_BUGON (int) ; 
 int /*<<< orphan*/  EFSCORRUPTED ; 
 int /*<<< orphan*/  ENOENT ; 
 int EROFS_BLKSIZ ; 
 TYPE_1__* EROFS_I (struct inode*) ; 
 struct page* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (struct page*) ; 
 int erofs_dirnamecmp (struct erofs_qstr*,struct erofs_qstr*,unsigned int*) ; 
 int /*<<< orphan*/  erofs_err (int /*<<< orphan*/ ,char*,int const,int /*<<< orphan*/ ) ; 
 int erofs_inode_datablocks (struct inode*) ; 
 struct erofs_dirent* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (struct erofs_dirent*) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int nameoff_from_disk (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 struct page* read_mapping_page (struct address_space* const,int const,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct page *find_target_block_classic(struct inode *dir,
					      struct erofs_qstr *name,
					      int *_ndirents)
{
	unsigned int startprfx, endprfx;
	int head, back;
	struct address_space *const mapping = dir->i_mapping;
	struct page *candidate = ERR_PTR(-ENOENT);

	startprfx = endprfx = 0;
	head = 0;
	back = erofs_inode_datablocks(dir) - 1;

	while (head <= back) {
		const int mid = head + (back - head) / 2;
		struct page *page = read_mapping_page(mapping, mid, NULL);

		if (!IS_ERR(page)) {
			struct erofs_dirent *de = kmap_atomic(page);
			const int nameoff = nameoff_from_disk(de->nameoff,
							      EROFS_BLKSIZ);
			const int ndirents = nameoff / sizeof(*de);
			int diff;
			unsigned int matched;
			struct erofs_qstr dname;

			if (!ndirents) {
				kunmap_atomic(de);
				put_page(page);
				erofs_err(dir->i_sb,
					  "corrupted dir block %d @ nid %llu",
					  mid, EROFS_I(dir)->nid);
				DBG_BUGON(1);
				page = ERR_PTR(-EFSCORRUPTED);
				goto out;
			}

			matched = min(startprfx, endprfx);

			dname.name = (u8 *)de + nameoff;
			if (ndirents == 1)
				dname.end = (u8 *)de + EROFS_BLKSIZ;
			else
				dname.end = (u8 *)de +
					nameoff_from_disk(de[1].nameoff,
							  EROFS_BLKSIZ);

			/* string comparison without already matched prefix */
			diff = erofs_dirnamecmp(name, &dname, &matched);
			kunmap_atomic(de);

			if (!diff) {
				*_ndirents = 0;
				goto out;
			} else if (diff > 0) {
				head = mid + 1;
				startprfx = matched;

				if (!IS_ERR(candidate))
					put_page(candidate);
				candidate = page;
				*_ndirents = ndirents;
			} else {
				put_page(page);

				back = mid - 1;
				endprfx = matched;
			}
			continue;
		}
out:		/* free if the candidate is valid */
		if (!IS_ERR(candidate))
			put_page(candidate);
		return page;
	}
	return candidate;
}