#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct soc_pcmcia_socket {int dummy; } ;
struct arcom_pcmcia_pdata {int /*<<< orphan*/  pwr_gpio; int /*<<< orphan*/  (* reset ) (int) ;} ;
struct TYPE_4__ {int flags; int Vcc; } ;
typedef  TYPE_1__ socket_state_t ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int SS_RESET ; 
 TYPE_3__* arcom_pcmcia_dev ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int) ; 
 struct arcom_pcmcia_pdata* viper_get_pdata () ; 

__attribute__((used)) static int viper_pcmcia_configure_socket(struct soc_pcmcia_socket *skt,
					 const socket_state_t *state)
{
	struct arcom_pcmcia_pdata *pdata = viper_get_pdata();

	/* Silently ignore Vpp, output enable, speaker enable. */
	pdata->reset(state->flags & SS_RESET);

	/* Apply socket voltage */
	switch (state->Vcc) {
	case 0:
		gpio_set_value(pdata->pwr_gpio, 0);
		break;
	case 33:
		gpio_set_value(pdata->pwr_gpio, 1);
		break;
	default:
		dev_err(&arcom_pcmcia_dev->dev, "Unsupported Vcc:%d\n", state->Vcc);
		return -1;
	}

	return 0;
}