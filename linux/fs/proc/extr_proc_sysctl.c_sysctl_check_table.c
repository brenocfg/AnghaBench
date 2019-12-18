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
struct ctl_table {scalar_t__ proc_handler; int mode; int /*<<< orphan*/  maxlen; int /*<<< orphan*/  data; scalar_t__ child; scalar_t__ procname; } ;

/* Variables and functions */
 int S_IRUGO ; 
 int S_IWUGO ; 
 scalar_t__ proc_dointvec ; 
 scalar_t__ proc_dointvec_jiffies ; 
 scalar_t__ proc_dointvec_minmax ; 
 scalar_t__ proc_dointvec_ms_jiffies ; 
 scalar_t__ proc_dointvec_userhz_jiffies ; 
 scalar_t__ proc_dostring ; 
 scalar_t__ proc_douintvec ; 
 scalar_t__ proc_douintvec_minmax ; 
 scalar_t__ proc_doulongvec_minmax ; 
 scalar_t__ proc_doulongvec_ms_jiffies_minmax ; 
 int sysctl_check_table_array (char const*,struct ctl_table*) ; 
 int sysctl_err (char const*,struct ctl_table*,char*,...) ; 

__attribute__((used)) static int sysctl_check_table(const char *path, struct ctl_table *table)
{
	int err = 0;
	for (; table->procname; table++) {
		if (table->child)
			err |= sysctl_err(path, table, "Not a file");

		if ((table->proc_handler == proc_dostring) ||
		    (table->proc_handler == proc_dointvec) ||
		    (table->proc_handler == proc_douintvec) ||
		    (table->proc_handler == proc_douintvec_minmax) ||
		    (table->proc_handler == proc_dointvec_minmax) ||
		    (table->proc_handler == proc_dointvec_jiffies) ||
		    (table->proc_handler == proc_dointvec_userhz_jiffies) ||
		    (table->proc_handler == proc_dointvec_ms_jiffies) ||
		    (table->proc_handler == proc_doulongvec_minmax) ||
		    (table->proc_handler == proc_doulongvec_ms_jiffies_minmax)) {
			if (!table->data)
				err |= sysctl_err(path, table, "No data");
			if (!table->maxlen)
				err |= sysctl_err(path, table, "No maxlen");
			else
				err |= sysctl_check_table_array(path, table);
		}
		if (!table->proc_handler)
			err |= sysctl_err(path, table, "No proc_handler");

		if ((table->mode & (S_IRUGO|S_IWUGO)) != table->mode)
			err |= sysctl_err(path, table, "bogus .mode 0%o",
				table->mode);
	}
	return err;
}