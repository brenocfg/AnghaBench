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
typedef  int /*<<< orphan*/  u32 ;
struct ramoops_context {scalar_t__ phys_addr; scalar_t__ size; int /*<<< orphan*/  memtype; int /*<<< orphan*/  ecc_info; } ;
struct persistent_ram_zone {int /*<<< orphan*/  type; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
typedef  scalar_t__ phys_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct persistent_ram_zone*) ; 
 int PTR_ERR (struct persistent_ram_zone*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,char const*,...) ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 struct persistent_ram_zone** kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct persistent_ram_zone**) ; 
 int /*<<< orphan*/  persistent_ram_free (struct persistent_ram_zone*) ; 
 struct persistent_ram_zone* persistent_ram_new (scalar_t__,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pstore_name_to_type (char const*) ; 

__attribute__((used)) static int ramoops_init_przs(const char *name,
			     struct device *dev, struct ramoops_context *cxt,
			     struct persistent_ram_zone ***przs,
			     phys_addr_t *paddr, size_t mem_sz,
			     ssize_t record_size,
			     unsigned int *cnt, u32 sig, u32 flags)
{
	int err = -ENOMEM;
	int i;
	size_t zone_sz;
	struct persistent_ram_zone **prz_ar;

	/* Allocate nothing for 0 mem_sz or 0 record_size. */
	if (mem_sz == 0 || record_size == 0) {
		*cnt = 0;
		return 0;
	}

	/*
	 * If we have a negative record size, calculate it based on
	 * mem_sz / *cnt. If we have a positive record size, calculate
	 * cnt from mem_sz / record_size.
	 */
	if (record_size < 0) {
		if (*cnt == 0)
			return 0;
		record_size = mem_sz / *cnt;
		if (record_size == 0) {
			dev_err(dev, "%s record size == 0 (%zu / %u)\n",
				name, mem_sz, *cnt);
			goto fail;
		}
	} else {
		*cnt = mem_sz / record_size;
		if (*cnt == 0) {
			dev_err(dev, "%s record count == 0 (%zu / %zu)\n",
				name, mem_sz, record_size);
			goto fail;
		}
	}

	if (*paddr + mem_sz - cxt->phys_addr > cxt->size) {
		dev_err(dev, "no room for %s mem region (0x%zx@0x%llx) in (0x%lx@0x%llx)\n",
			name,
			mem_sz, (unsigned long long)*paddr,
			cxt->size, (unsigned long long)cxt->phys_addr);
		goto fail;
	}

	zone_sz = mem_sz / *cnt;
	if (!zone_sz) {
		dev_err(dev, "%s zone size == 0\n", name);
		goto fail;
	}

	prz_ar = kcalloc(*cnt, sizeof(**przs), GFP_KERNEL);
	if (!prz_ar)
		goto fail;

	for (i = 0; i < *cnt; i++) {
		char *label;

		if (*cnt == 1)
			label = kasprintf(GFP_KERNEL, "ramoops:%s", name);
		else
			label = kasprintf(GFP_KERNEL, "ramoops:%s(%d/%d)",
					  name, i, *cnt - 1);
		prz_ar[i] = persistent_ram_new(*paddr, zone_sz, sig,
					       &cxt->ecc_info,
					       cxt->memtype, flags, label);
		if (IS_ERR(prz_ar[i])) {
			err = PTR_ERR(prz_ar[i]);
			dev_err(dev, "failed to request %s mem region (0x%zx@0x%llx): %d\n",
				name, record_size,
				(unsigned long long)*paddr, err);

			while (i > 0) {
				i--;
				persistent_ram_free(prz_ar[i]);
			}
			kfree(prz_ar);
			goto fail;
		}
		*paddr += zone_sz;
		prz_ar[i]->type = pstore_name_to_type(name);
	}

	*przs = prz_ar;
	return 0;

fail:
	*cnt = 0;
	return err;
}