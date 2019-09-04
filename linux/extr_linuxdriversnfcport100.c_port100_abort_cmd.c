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
struct port100 {int /*<<< orphan*/  in_urb; } ;
struct nfc_digital_dev {int dummy; } ;

/* Variables and functions */
 struct port100* nfc_digital_get_drvdata (struct nfc_digital_dev*) ; 
 int /*<<< orphan*/  port100_send_ack (struct port100*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void port100_abort_cmd(struct nfc_digital_dev *ddev)
{
	struct port100 *dev = nfc_digital_get_drvdata(ddev);

	/* An ack will cancel the last issued command */
	port100_send_ack(dev);

	/* cancel the urb request */
	usb_kill_urb(dev->in_urb);
}