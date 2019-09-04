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
struct pci_dev {int dummy; } ;
struct matrox_fb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  matroxfb_remove (struct matrox_fb_info*,int) ; 
 struct matrox_fb_info* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void pci_remove_matrox(struct pci_dev* pdev) {
	struct matrox_fb_info* minfo;

	minfo = pci_get_drvdata(pdev);
	matroxfb_remove(minfo, 1);
}