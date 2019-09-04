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
struct TYPE_2__ {char* name; int len; } ;
struct dentry {int /*<<< orphan*/  d_lock; int /*<<< orphan*/  d_parent; TYPE_1__ d_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 char* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXDEV ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ROOT (struct dentry*) ; 
 struct dentry* dget (struct dentry*) ; 
 struct dentry* dget_dlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 char* kstrdup (char*,int /*<<< orphan*/ ) ; 
 char* kstrndup (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* ovl_dentry_get_redirect (struct dentry*) ; 
 int ovl_redirect_max ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 

__attribute__((used)) static char *ovl_get_redirect(struct dentry *dentry, bool abs_redirect)
{
	char *buf, *ret;
	struct dentry *d, *tmp;
	int buflen = ovl_redirect_max + 1;

	if (!abs_redirect) {
		ret = kstrndup(dentry->d_name.name, dentry->d_name.len,
			       GFP_KERNEL);
		goto out;
	}

	buf = ret = kmalloc(buflen, GFP_KERNEL);
	if (!buf)
		goto out;

	buflen--;
	buf[buflen] = '\0';
	for (d = dget(dentry); !IS_ROOT(d);) {
		const char *name;
		int thislen;

		spin_lock(&d->d_lock);
		name = ovl_dentry_get_redirect(d);
		if (name) {
			thislen = strlen(name);
		} else {
			name = d->d_name.name;
			thislen = d->d_name.len;
		}

		/* If path is too long, fall back to userspace move */
		if (thislen + (name[0] != '/') > buflen) {
			ret = ERR_PTR(-EXDEV);
			spin_unlock(&d->d_lock);
			goto out_put;
		}

		buflen -= thislen;
		memcpy(&buf[buflen], name, thislen);
		tmp = dget_dlock(d->d_parent);
		spin_unlock(&d->d_lock);

		dput(d);
		d = tmp;

		/* Absolute redirect: finished */
		if (buf[buflen] == '/')
			break;
		buflen--;
		buf[buflen] = '/';
	}
	ret = kstrdup(&buf[buflen], GFP_KERNEL);
out_put:
	dput(d);
	kfree(buf);
out:
	return ret ? ret : ERR_PTR(-ENOMEM);
}