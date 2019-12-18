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
typedef  scalar_t__ phys_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct persistent_ram_zone*) ; 
 int /*<<< orphan*/  PRZ_FLAG_ZAP_OLD ; 
 int PTR_ERR (struct persistent_ram_zone*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,char const*,size_t,unsigned long long,int,...) ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 struct persistent_ram_zone* persistent_ram_new (scalar_t__,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pstore_name_to_type (char const*) ; 

__attribute__((used)) static int ramoops_init_prz(const char *name,
			    struct device *dev, struct ramoops_context *cxt,
			    struct persistent_ram_zone **prz,
			    phys_addr_t *paddr, size_t sz, u32 sig)
{
	char *label;

	if (!sz)
		return 0;

	if (*paddr + sz - cxt->phys_addr > cxt->size) {
		dev_err(dev, "no room for %s mem region (0x%zx@0x%llx) in (0x%lx@0x%llx)\n",
			name, sz, (unsigned long long)*paddr,
			cxt->size, (unsigned long long)cxt->phys_addr);
		return -ENOMEM;
	}

	label = kasprintf(GFP_KERNEL, "ramoops:%s", name);
	*prz = persistent_ram_new(*paddr, sz, sig, &cxt->ecc_info,
				  cxt->memtype, PRZ_FLAG_ZAP_OLD, label);
	if (IS_ERR(*prz)) {
		int err = PTR_ERR(*prz);

		dev_err(dev, "failed to request %s mem region (0x%zx@0x%llx): %d\n",
			name, sz, (unsigned long long)*paddr, err);
		return err;
	}

	*paddr += sz;
	(*prz)->type = pstore_name_to_type(name);

	return 0;
}