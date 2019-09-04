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
struct qstr {int dummy; } ;
struct ovl_fh {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct ovl_fh*) ; 
 int PTR_ERR (struct ovl_fh*) ; 
 int /*<<< orphan*/  kfree (struct ovl_fh*) ; 
 struct ovl_fh* ovl_encode_real_fh (struct dentry*,int) ; 
 int ovl_get_index_name_fh (struct ovl_fh*,struct qstr*) ; 

int ovl_get_index_name(struct dentry *origin, struct qstr *name)
{
	struct ovl_fh *fh;
	int err;

	fh = ovl_encode_real_fh(origin, false);
	if (IS_ERR(fh))
		return PTR_ERR(fh);

	err = ovl_get_index_name_fh(fh, name);

	kfree(fh);
	return err;
}