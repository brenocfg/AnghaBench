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
 void seq_put_decimal_ull_width (struct seq_file*,char const*,unsigned long long,int /*<<< orphan*/ ) ; 

void seq_put_decimal_ull(struct seq_file *m, const char *delimiter,
			 unsigned long long num)
{
	return seq_put_decimal_ull_width(m, delimiter, num, 0);
}