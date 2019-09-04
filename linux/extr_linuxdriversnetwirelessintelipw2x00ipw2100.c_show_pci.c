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
struct pci_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static ssize_t show_pci(struct device *d, struct device_attribute *attr,
			char *buf)
{
	struct pci_dev *pci_dev = to_pci_dev(d);
	char *out = buf;
	int i, j;
	u32 val;

	for (i = 0; i < 16; i++) {
		out += sprintf(out, "[%08X] ", i * 16);
		for (j = 0; j < 16; j += 4) {
			pci_read_config_dword(pci_dev, i * 16 + j, &val);
			out += sprintf(out, "%08X ", val);
		}
		out += sprintf(out, "\n");
	}

	return out - buf;
}