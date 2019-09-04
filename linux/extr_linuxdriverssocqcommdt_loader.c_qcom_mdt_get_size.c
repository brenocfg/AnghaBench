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
struct firmware {scalar_t__ data; } ;
struct elf32_phdr {scalar_t__ p_paddr; scalar_t__ p_memsz; } ;
struct elf32_hdr {int e_phnum; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ phys_addr_t ;

/* Variables and functions */
 scalar_t__ ALIGN (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ EINVAL ; 
 scalar_t__ PHYS_ADDR_MAX ; 
 int /*<<< orphan*/  SZ_4K ; 
 int /*<<< orphan*/  mdt_phdr_valid (struct elf32_phdr const*) ; 

ssize_t qcom_mdt_get_size(const struct firmware *fw)
{
	const struct elf32_phdr *phdrs;
	const struct elf32_phdr *phdr;
	const struct elf32_hdr *ehdr;
	phys_addr_t min_addr = PHYS_ADDR_MAX;
	phys_addr_t max_addr = 0;
	int i;

	ehdr = (struct elf32_hdr *)fw->data;
	phdrs = (struct elf32_phdr *)(ehdr + 1);

	for (i = 0; i < ehdr->e_phnum; i++) {
		phdr = &phdrs[i];

		if (!mdt_phdr_valid(phdr))
			continue;

		if (phdr->p_paddr < min_addr)
			min_addr = phdr->p_paddr;

		if (phdr->p_paddr + phdr->p_memsz > max_addr)
			max_addr = ALIGN(phdr->p_paddr + phdr->p_memsz, SZ_4K);
	}

	return min_addr < max_addr ? max_addr - min_addr : -EINVAL;
}