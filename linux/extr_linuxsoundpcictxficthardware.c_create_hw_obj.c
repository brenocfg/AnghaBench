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
struct hw {int chip_type; int model; struct pci_dev* pci; } ;
typedef  enum CTCARDS { ____Placeholder_CTCARDS } CTCARDS ;
typedef  enum CHIPTYP { ____Placeholder_CHIPTYP } CHIPTYP ;

/* Variables and functions */
#define  ATC20K1 129 
#define  ATC20K2 128 
 int ENODEV ; 
 int create_20k1_hw_obj (struct hw**) ; 
 int create_20k2_hw_obj (struct hw**) ; 

int create_hw_obj(struct pci_dev *pci, enum CHIPTYP chip_type,
		  enum CTCARDS model, struct hw **rhw)
{
	int err;

	switch (chip_type) {
	case ATC20K1:
		err = create_20k1_hw_obj(rhw);
		break;
	case ATC20K2:
		err = create_20k2_hw_obj(rhw);
		break;
	default:
		err = -ENODEV;
		break;
	}
	if (err)
		return err;

	(*rhw)->pci = pci;
	(*rhw)->chip_type = chip_type;
	(*rhw)->model = model;

	return 0;
}