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
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct integrity_iint_cache {TYPE_4__* ima_hash; } ;
struct dentry {int dummy; } ;
struct TYPE_6__ {scalar_t__ algo; int /*<<< orphan*/  type; } ;
struct TYPE_5__ {int /*<<< orphan*/  type; } ;
struct TYPE_7__ {int /*<<< orphan*/ * data; TYPE_2__ ng; TYPE_1__ sha1; } ;
struct TYPE_8__ {scalar_t__ algo; scalar_t__ length; TYPE_3__ xattr; } ;

/* Variables and functions */
 scalar_t__ HASH_ALGO_SHA1 ; 
 int /*<<< orphan*/  IMA_XATTR_DIGEST ; 
 int /*<<< orphan*/  IMA_XATTR_DIGEST_NG ; 
 int /*<<< orphan*/  XATTR_NAME_IMA ; 
 int __vfs_setxattr_noperm (struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ima_fix_xattr(struct dentry *dentry,
			 struct integrity_iint_cache *iint)
{
	int rc, offset;
	u8 algo = iint->ima_hash->algo;

	if (algo <= HASH_ALGO_SHA1) {
		offset = 1;
		iint->ima_hash->xattr.sha1.type = IMA_XATTR_DIGEST;
	} else {
		offset = 0;
		iint->ima_hash->xattr.ng.type = IMA_XATTR_DIGEST_NG;
		iint->ima_hash->xattr.ng.algo = algo;
	}
	rc = __vfs_setxattr_noperm(dentry, XATTR_NAME_IMA,
				   &iint->ima_hash->xattr.data[offset],
				   (sizeof(iint->ima_hash->xattr) - offset) +
				   iint->ima_hash->length, 0);
	return rc;
}