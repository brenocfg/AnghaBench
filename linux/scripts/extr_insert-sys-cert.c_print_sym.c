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
struct sym {unsigned long name; unsigned long address; unsigned long size; scalar_t__ offset; } ;
typedef  int /*<<< orphan*/  Elf_Ehdr ;

/* Variables and functions */
 int /*<<< orphan*/  info (char*,unsigned long) ; 

__attribute__((used)) static void print_sym(Elf_Ehdr *hdr, struct sym *s)
{
	info("sym:    %s\n", s->name);
	info("addr:   0x%lx\n", s->address);
	info("size:   %d\n", s->size);
	info("offset: 0x%lx\n", (unsigned long)s->offset);
}