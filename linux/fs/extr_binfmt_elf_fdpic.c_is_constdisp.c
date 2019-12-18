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
struct elfhdr {int dummy; } ;

/* Variables and functions */
 scalar_t__ elf_check_const_displacement (struct elfhdr*) ; 
 int /*<<< orphan*/  elf_check_fdpic (struct elfhdr*) ; 

__attribute__((used)) static int is_constdisp(struct elfhdr *hdr)
{
	if (!elf_check_fdpic(hdr))
		return 1;
	if (elf_check_const_displacement(hdr))
		return 1;
	return 0;
}