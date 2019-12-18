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
struct ubifs_info {int /*<<< orphan*/  ltab_sz; int /*<<< orphan*/  ltab_offs; int /*<<< orphan*/  ltab_lnum; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ubifs_leb_read (struct ubifs_info*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int unpack_ltab (struct ubifs_info*,void*) ; 
 int /*<<< orphan*/  vfree (void*) ; 
 void* vmalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_ltab(struct ubifs_info *c)
{
	int err;
	void *buf;

	buf = vmalloc(c->ltab_sz);
	if (!buf)
		return -ENOMEM;
	err = ubifs_leb_read(c, c->ltab_lnum, buf, c->ltab_offs, c->ltab_sz, 1);
	if (err)
		goto out;
	err = unpack_ltab(c, buf);
out:
	vfree(buf);
	return err;
}