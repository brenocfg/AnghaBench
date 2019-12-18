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
typedef  scalar_t__ u32 ;
struct extent_buffer {int dummy; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_path {scalar_t__* slots; struct extent_buffer** nodes; } ;
struct btrfs_key {scalar_t__ objectid; scalar_t__ type; int offset; } ;
struct btrfs_item {int dummy; } ;
struct btrfs_fs_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ BTRFS_EXTENT_CSUM_KEY ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct btrfs_root*) ; 
 int PTR_ERR (struct btrfs_root*) ; 
 int /*<<< orphan*/  TEST_ALLOC_EXTENT_BUFFER ; 
 int /*<<< orphan*/  TEST_ALLOC_FS_INFO ; 
 int /*<<< orphan*/  TEST_ALLOC_PATH ; 
 int /*<<< orphan*/  TEST_ALLOC_ROOT ; 
 struct extent_buffer* alloc_dummy_extent_buffer (struct btrfs_fs_info*,scalar_t__) ; 
 struct btrfs_fs_info* btrfs_alloc_dummy_fs_info (scalar_t__,scalar_t__) ; 
 struct btrfs_root* btrfs_alloc_dummy_root (struct btrfs_fs_info*) ; 
 struct btrfs_path* btrfs_alloc_path () ; 
 int /*<<< orphan*/  btrfs_free_dummy_fs_info (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_free_dummy_root (struct btrfs_root*) ; 
 int /*<<< orphan*/  btrfs_free_path (struct btrfs_path*) ; 
 int /*<<< orphan*/  btrfs_item_key_to_cpu (struct extent_buffer*,struct btrfs_key*,int) ; 
 struct btrfs_item* btrfs_item_nr (int) ; 
 int /*<<< orphan*/  btrfs_item_ptr_offset (struct extent_buffer*,int) ; 
 scalar_t__ btrfs_item_size (struct extent_buffer*,struct btrfs_item*) ; 
 int btrfs_split_item (int /*<<< orphan*/ *,struct btrfs_root*,struct btrfs_path*,struct btrfs_key*,int) ; 
 scalar_t__ memcmp (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  read_extent_buffer (struct extent_buffer*,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  setup_items_for_insert (struct btrfs_root*,struct btrfs_path*,struct btrfs_key*,scalar_t__*,scalar_t__,scalar_t__,int) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  test_err (char*,...) ; 
 int /*<<< orphan*/  test_msg (char*) ; 
 int /*<<< orphan*/  test_std_err (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_extent_buffer (struct extent_buffer*,char*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int test_btrfs_split_item(u32 sectorsize, u32 nodesize)
{
	struct btrfs_fs_info *fs_info;
	struct btrfs_path *path = NULL;
	struct btrfs_root *root = NULL;
	struct extent_buffer *eb;
	struct btrfs_item *item;
	char *value = "mary had a little lamb";
	char *split1 = "mary had a little";
	char *split2 = " lamb";
	char *split3 = "mary";
	char *split4 = " had a little";
	char buf[32];
	struct btrfs_key key;
	u32 value_len = strlen(value);
	int ret = 0;

	test_msg("running btrfs_split_item tests");

	fs_info = btrfs_alloc_dummy_fs_info(nodesize, sectorsize);
	if (!fs_info) {
		test_std_err(TEST_ALLOC_FS_INFO);
		return -ENOMEM;
	}

	root = btrfs_alloc_dummy_root(fs_info);
	if (IS_ERR(root)) {
		test_std_err(TEST_ALLOC_ROOT);
		ret = PTR_ERR(root);
		goto out;
	}

	path = btrfs_alloc_path();
	if (!path) {
		test_std_err(TEST_ALLOC_PATH);
		ret = -ENOMEM;
		goto out;
	}

	path->nodes[0] = eb = alloc_dummy_extent_buffer(fs_info, nodesize);
	if (!eb) {
		test_std_err(TEST_ALLOC_EXTENT_BUFFER);
		ret = -ENOMEM;
		goto out;
	}
	path->slots[0] = 0;

	key.objectid = 0;
	key.type = BTRFS_EXTENT_CSUM_KEY;
	key.offset = 0;

	setup_items_for_insert(root, path, &key, &value_len, value_len,
			       value_len + sizeof(struct btrfs_item), 1);
	item = btrfs_item_nr(0);
	write_extent_buffer(eb, value, btrfs_item_ptr_offset(eb, 0),
			    value_len);

	key.offset = 3;

	/*
	 * Passing NULL trans here should be safe because we have plenty of
	 * space in this leaf to split the item without having to split the
	 * leaf.
	 */
	ret = btrfs_split_item(NULL, root, path, &key, 17);
	if (ret) {
		test_err("split item failed %d", ret);
		goto out;
	}

	/*
	 * Read the first slot, it should have the original key and contain only
	 * 'mary had a little'
	 */
	btrfs_item_key_to_cpu(eb, &key, 0);
	if (key.objectid != 0 || key.type != BTRFS_EXTENT_CSUM_KEY ||
	    key.offset != 0) {
		test_err("invalid key at slot 0");
		ret = -EINVAL;
		goto out;
	}

	item = btrfs_item_nr(0);
	if (btrfs_item_size(eb, item) != strlen(split1)) {
		test_err("invalid len in the first split");
		ret = -EINVAL;
		goto out;
	}

	read_extent_buffer(eb, buf, btrfs_item_ptr_offset(eb, 0),
			   strlen(split1));
	if (memcmp(buf, split1, strlen(split1))) {
		test_err(
"data in the buffer doesn't match what it should in the first split have='%.*s' want '%s'",
			 (int)strlen(split1), buf, split1);
		ret = -EINVAL;
		goto out;
	}

	btrfs_item_key_to_cpu(eb, &key, 1);
	if (key.objectid != 0 || key.type != BTRFS_EXTENT_CSUM_KEY ||
	    key.offset != 3) {
		test_err("invalid key at slot 1");
		ret = -EINVAL;
		goto out;
	}

	item = btrfs_item_nr(1);
	if (btrfs_item_size(eb, item) != strlen(split2)) {
		test_err("invalid len in the second split");
		ret = -EINVAL;
		goto out;
	}

	read_extent_buffer(eb, buf, btrfs_item_ptr_offset(eb, 1),
			   strlen(split2));
	if (memcmp(buf, split2, strlen(split2))) {
		test_err(
	"data in the buffer doesn't match what it should in the second split");
		ret = -EINVAL;
		goto out;
	}

	key.offset = 1;
	/* Do it again so we test memmoving the other items in the leaf */
	ret = btrfs_split_item(NULL, root, path, &key, 4);
	if (ret) {
		test_err("second split item failed %d", ret);
		goto out;
	}

	btrfs_item_key_to_cpu(eb, &key, 0);
	if (key.objectid != 0 || key.type != BTRFS_EXTENT_CSUM_KEY ||
	    key.offset != 0) {
		test_err("invalid key at slot 0");
		ret = -EINVAL;
		goto out;
	}

	item = btrfs_item_nr(0);
	if (btrfs_item_size(eb, item) != strlen(split3)) {
		test_err("invalid len in the first split");
		ret = -EINVAL;
		goto out;
	}

	read_extent_buffer(eb, buf, btrfs_item_ptr_offset(eb, 0),
			   strlen(split3));
	if (memcmp(buf, split3, strlen(split3))) {
		test_err(
	"data in the buffer doesn't match what it should in the third split");
		ret = -EINVAL;
		goto out;
	}

	btrfs_item_key_to_cpu(eb, &key, 1);
	if (key.objectid != 0 || key.type != BTRFS_EXTENT_CSUM_KEY ||
	    key.offset != 1) {
		test_err("invalid key at slot 1");
		ret = -EINVAL;
		goto out;
	}

	item = btrfs_item_nr(1);
	if (btrfs_item_size(eb, item) != strlen(split4)) {
		test_err("invalid len in the second split");
		ret = -EINVAL;
		goto out;
	}

	read_extent_buffer(eb, buf, btrfs_item_ptr_offset(eb, 1),
			   strlen(split4));
	if (memcmp(buf, split4, strlen(split4))) {
		test_err(
	"data in the buffer doesn't match what it should in the fourth split");
		ret = -EINVAL;
		goto out;
	}

	btrfs_item_key_to_cpu(eb, &key, 2);
	if (key.objectid != 0 || key.type != BTRFS_EXTENT_CSUM_KEY ||
	    key.offset != 3) {
		test_err("invalid key at slot 2");
		ret = -EINVAL;
		goto out;
	}

	item = btrfs_item_nr(2);
	if (btrfs_item_size(eb, item) != strlen(split2)) {
		test_err("invalid len in the second split");
		ret = -EINVAL;
		goto out;
	}

	read_extent_buffer(eb, buf, btrfs_item_ptr_offset(eb, 2),
			   strlen(split2));
	if (memcmp(buf, split2, strlen(split2))) {
		test_err(
	"data in the buffer doesn't match what it should in the last chunk");
		ret = -EINVAL;
		goto out;
	}
out:
	btrfs_free_path(path);
	btrfs_free_dummy_root(root);
	btrfs_free_dummy_fs_info(fs_info);
	return ret;
}