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
typedef  unsigned int u8 ;
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,unsigned int) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 

__attribute__((used)) static inline void emit_byte(struct seq_file *m, unsigned int offset, u8 byte)
{
	if ((offset & 0xf) == 0) {
		if (offset != 0)
			seq_putc(m, '\n');
		seq_printf(m, "%08x:", offset);
	}
	if ((offset & 0x1) == 0)
		seq_putc(m, ' ');
	seq_printf(m, "%02x", byte);
}