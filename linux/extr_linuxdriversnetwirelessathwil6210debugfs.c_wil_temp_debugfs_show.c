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
struct wil6210_priv {int dummy; } ;
struct seq_file {struct wil6210_priv* private; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  print_temp (struct seq_file*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int wmi_get_temperature (struct wil6210_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wil_temp_debugfs_show(struct seq_file *s, void *data)
{
	struct wil6210_priv *wil = s->private;
	s32 t_m, t_r;
	int rc = wmi_get_temperature(wil, &t_m, &t_r);

	if (rc) {
		seq_puts(s, "Failed\n");
		return 0;
	}

	print_temp(s, "T_mac   =", t_m);
	print_temp(s, "T_radio =", t_r);

	return 0;
}