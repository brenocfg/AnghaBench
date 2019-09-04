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
struct pcmcia_socket {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_BATTDEAD ; 
 int /*<<< orphan*/  GPIO_BATTWARN ; 
 int /*<<< orphan*/  GPIO_CDA ; 
 int /*<<< orphan*/  GPIO_CDB ; 
 int /*<<< orphan*/  GPIO_POWER ; 
 int /*<<< orphan*/  GPIO_RESET ; 
 int /*<<< orphan*/  GPIO_VSH ; 
 int /*<<< orphan*/  GPIO_VSL ; 
 unsigned int SS_3VCARD ; 
 unsigned int SS_BATDEAD ; 
 unsigned int SS_BATWARN ; 
 unsigned int SS_DETECT ; 
 unsigned int SS_POWERON ; 
 unsigned int SS_READY ; 
 unsigned int SS_RESET ; 
 unsigned int SS_XVCARD ; 
 scalar_t__ gpio_get_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xxs1500_pcmcia_get_status(struct pcmcia_socket *skt,
				     unsigned int *value)
{
	unsigned int status;
	int i;

	status = 0;

	/* check carddetects: GPIO[0:1] must both be low */
	if (!gpio_get_value(GPIO_CDA) && !gpio_get_value(GPIO_CDB))
		status |= SS_DETECT;

	/* determine card voltage: GPIO[208:209] binary value */
	i = (!!gpio_get_value(GPIO_VSL)) | ((!!gpio_get_value(GPIO_VSH)) << 1);

	switch (i) {
	case 0:
	case 1:
	case 2:
		status |= SS_3VCARD;	/* 3V card */
		break;
	case 3:				/* 5V card, unsupported */
	default:
		status |= SS_XVCARD;	/* treated as unsupported in core */
	}

	/* GPIO214: low active power switch */
	status |= gpio_get_value(GPIO_POWER) ? 0 : SS_POWERON;

	/* GPIO204: high-active reset line */
	status |= gpio_get_value(GPIO_RESET) ? SS_RESET : SS_READY;

	/* other stuff */
	status |= gpio_get_value(GPIO_BATTDEAD) ? 0 : SS_BATDEAD;
	status |= gpio_get_value(GPIO_BATTWARN) ? 0 : SS_BATWARN;

	*value = status;

	return 0;
}