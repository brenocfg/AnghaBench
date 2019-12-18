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
struct inode {int /*<<< orphan*/  i_size; } ;
struct TYPE_3__ {int /*<<< orphan*/  digest_size; TYPE_2__* hash_alg; } ;
struct fsverity_info {int /*<<< orphan*/  measurement; TYPE_1__ tree_params; int /*<<< orphan*/  root_hash; struct inode const* inode; } ;
struct fsverity_descriptor {int version; int salt_size; int /*<<< orphan*/  root_hash; int /*<<< orphan*/  salt; int /*<<< orphan*/  log_blocksize; int /*<<< orphan*/  hash_algorithm; int /*<<< orphan*/  data_size; int /*<<< orphan*/  __reserved; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct fsverity_info* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int compute_file_measurement (TYPE_2__*,struct fsverity_descriptor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsverity_err (struct inode const*,char*,...) ; 
 int /*<<< orphan*/  fsverity_free_info (struct fsverity_info*) ; 
 int /*<<< orphan*/  fsverity_info_cachep ; 
 int fsverity_init_merkle_tree_params (TYPE_1__*,struct inode const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int fsverity_verify_signature (struct fsverity_info*,struct fsverity_descriptor*,size_t) ; 
 struct fsverity_info* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ memchr_inv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct fsverity_info *fsverity_create_info(const struct inode *inode,
					   void *_desc, size_t desc_size)
{
	struct fsverity_descriptor *desc = _desc;
	struct fsverity_info *vi;
	int err;

	if (desc_size < sizeof(*desc)) {
		fsverity_err(inode, "Unrecognized descriptor size: %zu bytes",
			     desc_size);
		return ERR_PTR(-EINVAL);
	}

	if (desc->version != 1) {
		fsverity_err(inode, "Unrecognized descriptor version: %u",
			     desc->version);
		return ERR_PTR(-EINVAL);
	}

	if (memchr_inv(desc->__reserved, 0, sizeof(desc->__reserved))) {
		fsverity_err(inode, "Reserved bits set in descriptor");
		return ERR_PTR(-EINVAL);
	}

	if (desc->salt_size > sizeof(desc->salt)) {
		fsverity_err(inode, "Invalid salt_size: %u", desc->salt_size);
		return ERR_PTR(-EINVAL);
	}

	if (le64_to_cpu(desc->data_size) != inode->i_size) {
		fsverity_err(inode,
			     "Wrong data_size: %llu (desc) != %lld (inode)",
			     le64_to_cpu(desc->data_size), inode->i_size);
		return ERR_PTR(-EINVAL);
	}

	vi = kmem_cache_zalloc(fsverity_info_cachep, GFP_KERNEL);
	if (!vi)
		return ERR_PTR(-ENOMEM);
	vi->inode = inode;

	err = fsverity_init_merkle_tree_params(&vi->tree_params, inode,
					       desc->hash_algorithm,
					       desc->log_blocksize,
					       desc->salt, desc->salt_size);
	if (err) {
		fsverity_err(inode,
			     "Error %d initializing Merkle tree parameters",
			     err);
		goto out;
	}

	memcpy(vi->root_hash, desc->root_hash, vi->tree_params.digest_size);

	err = compute_file_measurement(vi->tree_params.hash_alg, desc,
				       vi->measurement);
	if (err) {
		fsverity_err(inode, "Error %d computing file measurement", err);
		goto out;
	}
	pr_debug("Computed file measurement: %s:%*phN\n",
		 vi->tree_params.hash_alg->name,
		 vi->tree_params.digest_size, vi->measurement);

	err = fsverity_verify_signature(vi, desc, desc_size);
out:
	if (err) {
		fsverity_free_info(vi);
		vi = ERR_PTR(err);
	}
	return vi;
}