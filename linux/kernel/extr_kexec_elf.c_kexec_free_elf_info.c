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
struct kexec_elf_info {int /*<<< orphan*/  proghdrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct kexec_elf_info*,int /*<<< orphan*/ ,int) ; 

void kexec_free_elf_info(struct kexec_elf_info *elf_info)
{
	kfree(elf_info->proghdrs);
	memset(elf_info, 0, sizeof(*elf_info));
}