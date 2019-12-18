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
 int /*<<< orphan*/  HEX_PREFIX ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  pr_fmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_hex_dump (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,void const*,size_t,int) ; 
 int /*<<< orphan*/  seq_hex_dump (struct seq_file*,int /*<<< orphan*/ ,int,int,int,void const*,size_t,int) ; 

__attribute__((used)) static void warn_or_seq_hex_dump(struct seq_file *seq, int prefix_type,
				 int rowsize, int groupsize, const void *buf,
				 size_t len, bool ascii)
{
	if (seq)
		seq_hex_dump(seq, HEX_PREFIX, prefix_type, rowsize, groupsize,
			     buf, len, ascii);
	else
		print_hex_dump(KERN_WARNING, pr_fmt(HEX_PREFIX), prefix_type,
			       rowsize, groupsize, buf, len, ascii);
}