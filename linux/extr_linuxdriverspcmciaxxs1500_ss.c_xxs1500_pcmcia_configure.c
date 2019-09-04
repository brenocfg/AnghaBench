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
struct xxs1500_pcmcia_sock {unsigned int old_flags; } ;
struct socket_state_t {int Vcc; unsigned int flags; } ;
struct pcmcia_socket {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GPIO_OUTEN ; 
 int /*<<< orphan*/  GPIO_POWER ; 
 int /*<<< orphan*/  GPIO_RESET ; 
 unsigned int SS_RESET ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct xxs1500_pcmcia_sock* to_xxs_socket (struct pcmcia_socket*) ; 

__attribute__((used)) static int xxs1500_pcmcia_configure(struct pcmcia_socket *skt,
				    struct socket_state_t *state)
{
	struct xxs1500_pcmcia_sock *sock = to_xxs_socket(skt);
	unsigned int changed;

	/* power control */
	switch (state->Vcc) {
	case 0:
		gpio_set_value(GPIO_POWER, 1);	/* power off */
		break;
	case 33:
		gpio_set_value(GPIO_POWER, 0);	/* power on */
		break;
	case 50:
	default:
		return -EINVAL;
	}

	changed = state->flags ^ sock->old_flags;

	if (changed & SS_RESET) {
		if (state->flags & SS_RESET) {
			gpio_set_value(GPIO_RESET, 1);	/* assert reset */
			gpio_set_value(GPIO_OUTEN, 1);	/* buffers off */
		} else {
			gpio_set_value(GPIO_RESET, 0);	/* deassert reset */
			gpio_set_value(GPIO_OUTEN, 0);	/* buffers on */
			msleep(500);
		}
	}

	sock->old_flags = state->flags;

	return 0;
}