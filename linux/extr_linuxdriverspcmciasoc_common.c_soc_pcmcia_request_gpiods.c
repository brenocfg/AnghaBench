#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct device* parent; } ;
struct TYPE_5__ {TYPE_1__ dev; } ;
struct soc_pcmcia_socket {TYPE_3__* stat; TYPE_2__ socket; } ;
struct gpio_desc {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_6__ {struct gpio_desc* desc; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_3__*) ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int PTR_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,int) ; 
 struct gpio_desc* devm_gpiod_get (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int soc_pcmcia_request_gpiods(struct soc_pcmcia_socket *skt)
{
	struct device *dev = skt->socket.dev.parent;
	struct gpio_desc *desc;
	int i;

	for (i = 0; i < ARRAY_SIZE(skt->stat); i++) {
		if (!skt->stat[i].name)
			continue;

		desc = devm_gpiod_get(dev, skt->stat[i].name, GPIOD_IN);
		if (IS_ERR(desc)) {
			dev_err(dev, "Failed to get GPIO for %s: %ld\n",
				skt->stat[i].name, PTR_ERR(desc));
			return PTR_ERR(desc);
		}

		skt->stat[i].desc = desc;
	}

	return 0;
}