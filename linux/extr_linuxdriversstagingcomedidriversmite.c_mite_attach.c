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
struct pci_dev {int dummy; } ;
struct mite {scalar_t__ mmio; TYPE_1__* channels; struct pci_dev* pcidev; int /*<<< orphan*/  lock; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {unsigned int channel; int done; struct mite* mite; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int MAX_MITE_DMA_CHANNELS ; 
 struct pci_dev* comedi_to_pci_dev (struct comedi_device*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct mite*) ; 
 struct mite* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mite_setup (struct comedi_device*,struct mite*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct mite *mite_attach(struct comedi_device *dev, bool use_win1)
{
	struct pci_dev *pcidev = comedi_to_pci_dev(dev);
	struct mite *mite;
	unsigned int i;
	int ret;

	mite = kzalloc(sizeof(*mite), GFP_KERNEL);
	if (!mite)
		return NULL;

	spin_lock_init(&mite->lock);
	mite->pcidev = pcidev;
	for (i = 0; i < MAX_MITE_DMA_CHANNELS; ++i) {
		mite->channels[i].mite = mite;
		mite->channels[i].channel = i;
		mite->channels[i].done = 1;
	}

	ret = mite_setup(dev, mite, use_win1);
	if (ret) {
		if (mite->mmio)
			iounmap(mite->mmio);
		kfree(mite);
		return NULL;
	}

	return mite;
}