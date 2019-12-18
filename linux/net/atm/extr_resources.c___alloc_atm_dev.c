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
struct atm_dev {char const* type; int /*<<< orphan*/  lecs; int /*<<< orphan*/  local; int /*<<< orphan*/  lock; int /*<<< orphan*/  link_rate; int /*<<< orphan*/  signal; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATM_OC3_PCR ; 
 int /*<<< orphan*/  ATM_PHY_SIG_UNKNOWN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct atm_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct atm_dev *__alloc_atm_dev(const char *type)
{
	struct atm_dev *dev;

	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev)
		return NULL;
	dev->type = type;
	dev->signal = ATM_PHY_SIG_UNKNOWN;
	dev->link_rate = ATM_OC3_PCR;
	spin_lock_init(&dev->lock);
	INIT_LIST_HEAD(&dev->local);
	INIT_LIST_HEAD(&dev->lecs);

	return dev;
}