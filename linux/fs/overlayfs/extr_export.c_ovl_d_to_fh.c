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
struct ovl_fh {int len; int /*<<< orphan*/  type; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int EOVERFLOW ; 
 scalar_t__ IS_ERR (struct ovl_fh*) ; 
 int PTR_ERR (struct ovl_fh*) ; 
 int /*<<< orphan*/  kfree (struct ovl_fh*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int ovl_check_encode_origin (struct dentry*) ; 
 int /*<<< orphan*/  ovl_dentry_lower (struct dentry*) ; 
 int /*<<< orphan*/  ovl_dentry_upper (struct dentry*) ; 
 struct ovl_fh* ovl_encode_real_fh (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*,struct dentry*,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ovl_d_to_fh(struct dentry *dentry, char *buf, int buflen)
{
	struct ovl_fh *fh = NULL;
	int err, enc_lower;

	/*
	 * Check if we should encode a lower or upper file handle and maybe
	 * copy up an ancestor to make lower file handle connectable.
	 */
	err = enc_lower = ovl_check_encode_origin(dentry);
	if (enc_lower < 0)
		goto fail;

	/* Encode an upper or lower file handle */
	fh = ovl_encode_real_fh(enc_lower ? ovl_dentry_lower(dentry) :
				ovl_dentry_upper(dentry), !enc_lower);
	if (IS_ERR(fh))
		return PTR_ERR(fh);

	err = -EOVERFLOW;
	if (fh->len > buflen)
		goto fail;

	memcpy(buf, (char *)fh, fh->len);
	err = fh->len;

out:
	kfree(fh);
	return err;

fail:
	pr_warn_ratelimited("overlayfs: failed to encode file handle (%pd2, err=%i, buflen=%d, len=%d, type=%d)\n",
			    dentry, err, buflen, fh ? (int)fh->len : 0,
			    fh ? fh->type : 0);
	goto out;
}