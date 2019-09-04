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
typedef  int /*<<< orphan*/  u8 ;
struct device {int dummy; } ;
struct rproc {size_t table_sz; scalar_t__ cached_table; scalar_t__ table_ptr; struct device dev; } ;
struct resource_table {int dummy; } ;
struct firmware {int /*<<< orphan*/  size; int /*<<< orphan*/ * data; } ;
struct elf32_shdr {int sh_offset; size_t sh_size; } ;
struct elf32_hdr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct elf32_shdr* find_table (struct device*,struct elf32_hdr*,int /*<<< orphan*/ ) ; 
 scalar_t__ kmemdup (struct resource_table*,size_t,int /*<<< orphan*/ ) ; 

int rproc_elf_load_rsc_table(struct rproc *rproc, const struct firmware *fw)
{
	struct elf32_hdr *ehdr;
	struct elf32_shdr *shdr;
	struct device *dev = &rproc->dev;
	struct resource_table *table = NULL;
	const u8 *elf_data = fw->data;
	size_t tablesz;

	ehdr = (struct elf32_hdr *)elf_data;

	shdr = find_table(dev, ehdr, fw->size);
	if (!shdr)
		return -EINVAL;

	table = (struct resource_table *)(elf_data + shdr->sh_offset);
	tablesz = shdr->sh_size;

	/*
	 * Create a copy of the resource table. When a virtio device starts
	 * and calls vring_new_virtqueue() the address of the allocated vring
	 * will be stored in the cached_table. Before the device is started,
	 * cached_table will be copied into device memory.
	 */
	rproc->cached_table = kmemdup(table, tablesz, GFP_KERNEL);
	if (!rproc->cached_table)
		return -ENOMEM;

	rproc->table_ptr = rproc->cached_table;
	rproc->table_sz = tablesz;

	return 0;
}