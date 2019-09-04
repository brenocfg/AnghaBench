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
struct wil6210_priv {scalar_t__* fw_version; } ;
struct seq_file {struct wil6210_priv* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,scalar_t__*) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int wil_fw_version_debugfs_show(struct seq_file *s, void *data)
{
	struct wil6210_priv *wil = s->private;

	if (wil->fw_version[0])
		seq_printf(s, "%s\n", wil->fw_version);
	else
		seq_puts(s, "N/A\n");

	return 0;
}