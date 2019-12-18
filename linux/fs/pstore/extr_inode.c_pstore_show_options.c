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
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ PSTORE_DEFAULT_KMSG_BYTES ; 
 scalar_t__ kmsg_bytes ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,scalar_t__) ; 

__attribute__((used)) static int pstore_show_options(struct seq_file *m, struct dentry *root)
{
	if (kmsg_bytes != PSTORE_DEFAULT_KMSG_BYTES)
		seq_printf(m, ",kmsg_bytes=%lu", kmsg_bytes);
	return 0;
}