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
struct file {int /*<<< orphan*/  f_path; } ;

/* Variables and functions */
 int seq_path (struct seq_file*,int /*<<< orphan*/ *,char const*) ; 

int seq_file_path(struct seq_file *m, struct file *file, const char *esc)
{
	return seq_path(m, &file->f_path, esc);
}