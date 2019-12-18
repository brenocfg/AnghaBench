#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int e_machine; } ;
struct elf {TYPE_1__ ehdr; } ;

/* Variables and functions */
#define  EM_386 129 
#define  EM_X86_64 128 
 int /*<<< orphan*/  WARN (char*,int) ; 

__attribute__((used)) static int is_x86_64(struct elf *elf)
{
	switch (elf->ehdr.e_machine) {
	case EM_X86_64:
		return 1;
	case EM_386:
		return 0;
	default:
		WARN("unexpected ELF machine type %d", elf->ehdr.e_machine);
		return -1;
	}
}