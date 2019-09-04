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
struct seq_file {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ pnp_bios_get_stat_res (void*) ; 
 int /*<<< orphan*/  seq_write (struct seq_file*,void*,int) ; 

__attribute__((used)) static int pnp_legacyres_proc_show(struct seq_file *m, void *v)
{
	void *buf;

	buf = kmalloc(65536, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;
	if (pnp_bios_get_stat_res(buf)) {
		kfree(buf);
		return -EIO;
	}

	seq_write(m, buf, 65536);
	kfree(buf);
	return 0;
}