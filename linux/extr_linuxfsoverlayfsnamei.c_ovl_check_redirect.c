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
struct ovl_lookup_data {int stop; char* redirect; TYPE_1__ name; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (char*) ; 
 int PTR_ERR (char*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 char* ovl_get_redirect_xattr (struct dentry*,size_t) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int ovl_check_redirect(struct dentry *dentry, struct ovl_lookup_data *d,
			      size_t prelen, const char *post)
{
	int res;
	char *buf;

	buf = ovl_get_redirect_xattr(dentry, prelen + strlen(post));
	if (IS_ERR_OR_NULL(buf))
		return PTR_ERR(buf);

	if (buf[0] == '/') {
		/*
		 * One of the ancestor path elements in an absolute path
		 * lookup in ovl_lookup_layer() could have been opaque and
		 * that will stop further lookup in lower layers (d->stop=true)
		 * But we have found an absolute redirect in decendant path
		 * element and that should force continue lookup in lower
		 * layers (reset d->stop).
		 */
		d->stop = false;
	} else {
		res = strlen(buf) + 1;
		memmove(buf + prelen, buf, res);
		memcpy(buf, d->name.name, prelen);
	}

	strcat(buf, post);
	kfree(d->redirect);
	d->redirect = buf;
	d->name.name = d->redirect;
	d->name.len = strlen(d->redirect);

	return 0;
}