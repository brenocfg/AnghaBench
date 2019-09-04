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
struct fst_card_info {int nports; size_t type; int /*<<< orphan*/  irq; TYPE_2__* ports; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 TYPE_1__* port_to_dev (TYPE_2__*) ; 
 int /*<<< orphan*/  pr_err (char*,int,int) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int register_hdlc_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * type_strings ; 
 int /*<<< orphan*/  unregister_hdlc_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fst_init_card(struct fst_card_info *card)
{
	int i;
	int err;

	/* We're working on a number of ports based on the card ID. If the
	 * firmware detects something different later (should never happen)
	 * we'll have to revise it in some way then.
	 */
	for (i = 0; i < card->nports; i++) {
		err = register_hdlc_device(card->ports[i].dev);
		if (err < 0) {
			pr_err("Cannot register HDLC device for port %d (errno %d)\n",
				i, -err);
			while (i--)
				unregister_hdlc_device(card->ports[i].dev);
			return err;
		}
	}

	pr_info("%s-%s: %s IRQ%d, %d ports\n",
		port_to_dev(&card->ports[0])->name,
		port_to_dev(&card->ports[card->nports - 1])->name,
		type_strings[card->type], card->irq, card->nports);
	return 0;
}