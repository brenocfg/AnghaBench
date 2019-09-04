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
typedef  int vm_flags_t ;
struct seq_file {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 unsigned long long MAJOR (int /*<<< orphan*/ ) ; 
 unsigned long long MINOR (int /*<<< orphan*/ ) ; 
 int VM_EXEC ; 
 int VM_MAYSHARE ; 
 int VM_READ ; 
 int VM_WRITE ; 
 int /*<<< orphan*/  seq_put_decimal_ull (struct seq_file*,char*,unsigned long) ; 
 int /*<<< orphan*/  seq_put_hex_ll (struct seq_file*,char*,unsigned long long,int) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 int /*<<< orphan*/  seq_setwidth (struct seq_file*,int) ; 

__attribute__((used)) static void show_vma_header_prefix(struct seq_file *m,
				   unsigned long start, unsigned long end,
				   vm_flags_t flags, unsigned long long pgoff,
				   dev_t dev, unsigned long ino)
{
	seq_setwidth(m, 25 + sizeof(void *) * 6 - 1);
	seq_put_hex_ll(m, NULL, start, 8);
	seq_put_hex_ll(m, "-", end, 8);
	seq_putc(m, ' ');
	seq_putc(m, flags & VM_READ ? 'r' : '-');
	seq_putc(m, flags & VM_WRITE ? 'w' : '-');
	seq_putc(m, flags & VM_EXEC ? 'x' : '-');
	seq_putc(m, flags & VM_MAYSHARE ? 's' : 'p');
	seq_put_hex_ll(m, " ", pgoff, 8);
	seq_put_hex_ll(m, " ", MAJOR(dev), 2);
	seq_put_hex_ll(m, ":", MINOR(dev), 2);
	seq_put_decimal_ull(m, " ", ino);
	seq_putc(m, ' ');
}