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
typedef  int u32 ;
typedef  int resource_size_t ;

/* Variables and functions */
 int EINVAL ; 
 int FARADAY_PCI_MEMBASE_MASK ; 
 int FARADAY_PCI_MEMSIZE_128MB ; 
 int FARADAY_PCI_MEMSIZE_16MB ; 
 int FARADAY_PCI_MEMSIZE_1GB ; 
 int FARADAY_PCI_MEMSIZE_1MB ; 
 int FARADAY_PCI_MEMSIZE_256MB ; 
 int FARADAY_PCI_MEMSIZE_2GB ; 
 int FARADAY_PCI_MEMSIZE_2MB ; 
 int FARADAY_PCI_MEMSIZE_32MB ; 
 int FARADAY_PCI_MEMSIZE_4MB ; 
 int FARADAY_PCI_MEMSIZE_512MB ; 
 int FARADAY_PCI_MEMSIZE_64MB ; 
 int FARADAY_PCI_MEMSIZE_8MB ; 
 int FARADAY_PCI_MEMSIZE_SHIFT ; 
#define  SZ_128M 139 
#define  SZ_16M 138 
#define  SZ_1G 137 
#define  SZ_1M 136 
#define  SZ_256M 135 
#define  SZ_2G 134 
#define  SZ_2M 133 
#define  SZ_32M 132 
#define  SZ_4M 131 
#define  SZ_512M 130 
#define  SZ_64M 129 
#define  SZ_8M 128 
 int /*<<< orphan*/  pr_debug (char*,int*,int*,int) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static int faraday_res_to_memcfg(resource_size_t mem_base,
				 resource_size_t mem_size, u32 *val)
{
	u32 outval;

	switch (mem_size) {
	case SZ_1M:
		outval = FARADAY_PCI_MEMSIZE_1MB;
		break;
	case SZ_2M:
		outval = FARADAY_PCI_MEMSIZE_2MB;
		break;
	case SZ_4M:
		outval = FARADAY_PCI_MEMSIZE_4MB;
		break;
	case SZ_8M:
		outval = FARADAY_PCI_MEMSIZE_8MB;
		break;
	case SZ_16M:
		outval = FARADAY_PCI_MEMSIZE_16MB;
		break;
	case SZ_32M:
		outval = FARADAY_PCI_MEMSIZE_32MB;
		break;
	case SZ_64M:
		outval = FARADAY_PCI_MEMSIZE_64MB;
		break;
	case SZ_128M:
		outval = FARADAY_PCI_MEMSIZE_128MB;
		break;
	case SZ_256M:
		outval = FARADAY_PCI_MEMSIZE_256MB;
		break;
	case SZ_512M:
		outval = FARADAY_PCI_MEMSIZE_512MB;
		break;
	case SZ_1G:
		outval = FARADAY_PCI_MEMSIZE_1GB;
		break;
	case SZ_2G:
		outval = FARADAY_PCI_MEMSIZE_2GB;
		break;
	default:
		return -EINVAL;
	}
	outval <<= FARADAY_PCI_MEMSIZE_SHIFT;

	/* This is probably not good */
	if (mem_base & ~(FARADAY_PCI_MEMBASE_MASK))
		pr_warn("truncated PCI memory base\n");
	/* Translate to bridge side address space */
	outval |= (mem_base & FARADAY_PCI_MEMBASE_MASK);
	pr_debug("Translated pci base @%pap, size %pap to config %08x\n",
		 &mem_base, &mem_size, outval);

	*val = outval;
	return 0;
}