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
struct ubifs_info {int /*<<< orphan*/  ubi; } ;

/* Variables and functions */
 int EBADMSG ; 
 int /*<<< orphan*/  dump_stack () ; 
 int ubi_read (int /*<<< orphan*/ ,int,void*,int,int) ; 
 int /*<<< orphan*/  ubifs_err (struct ubifs_info const*,char*,int,int,int,int) ; 

int ubifs_leb_read(const struct ubifs_info *c, int lnum, void *buf, int offs,
		   int len, int even_ebadmsg)
{
	int err;

	err = ubi_read(c->ubi, lnum, buf, offs, len);
	/*
	 * In case of %-EBADMSG print the error message only if the
	 * @even_ebadmsg is true.
	 */
	if (err && (err != -EBADMSG || even_ebadmsg)) {
		ubifs_err(c, "reading %d bytes from LEB %d:%d failed, error %d",
			  len, lnum, offs, err);
		dump_stack();
	}
	return err;
}