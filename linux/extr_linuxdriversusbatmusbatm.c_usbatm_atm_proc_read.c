#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usbatm_data {char* description; scalar_t__ disconnected; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_drop; int /*<<< orphan*/  rx_err; int /*<<< orphan*/  rx; int /*<<< orphan*/  tx_err; int /*<<< orphan*/  tx; } ;
struct TYPE_4__ {TYPE_1__ aal5; } ;
struct atm_dev {int signal; TYPE_2__ stats; int /*<<< orphan*/  esi; struct usbatm_data* dev_data; } ;
typedef  int loff_t ;

/* Variables and functions */
#define  ATM_PHY_SIG_FOUND 129 
#define  ATM_PHY_SIG_LOST 128 
 int ENODEV ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int sprintf (char*,char*,...) ; 

__attribute__((used)) static int usbatm_atm_proc_read(struct atm_dev *atm_dev, loff_t *pos, char *page)
{
	struct usbatm_data *instance = atm_dev->dev_data;
	int left = *pos;

	if (!instance)
		return -ENODEV;

	if (!left--)
		return sprintf(page, "%s\n", instance->description);

	if (!left--)
		return sprintf(page, "MAC: %pM\n", atm_dev->esi);

	if (!left--)
		return sprintf(page,
			       "AAL5: tx %d ( %d err ), rx %d ( %d err, %d drop )\n",
			       atomic_read(&atm_dev->stats.aal5.tx),
			       atomic_read(&atm_dev->stats.aal5.tx_err),
			       atomic_read(&atm_dev->stats.aal5.rx),
			       atomic_read(&atm_dev->stats.aal5.rx_err),
			       atomic_read(&atm_dev->stats.aal5.rx_drop));

	if (!left--) {
		if (instance->disconnected)
			return sprintf(page, "Disconnected\n");
		else
			switch (atm_dev->signal) {
			case ATM_PHY_SIG_FOUND:
				return sprintf(page, "Line up\n");
			case ATM_PHY_SIG_LOST:
				return sprintf(page, "Line down\n");
			default:
				return sprintf(page, "Line state unknown\n");
			}
	}

	return 0;
}