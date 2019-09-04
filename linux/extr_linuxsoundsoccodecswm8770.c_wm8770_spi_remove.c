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
struct wm8770_priv {int /*<<< orphan*/ * disable_nb; TYPE_1__* supplies; } ;
struct spi_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  consumer; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  regulator_unregister_notifier (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct wm8770_priv* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int wm8770_spi_remove(struct spi_device *spi)
{
	struct wm8770_priv *wm8770 = spi_get_drvdata(spi);
	int i;

	for (i = 0; i < ARRAY_SIZE(wm8770->supplies); ++i)
		regulator_unregister_notifier(wm8770->supplies[i].consumer,
					      &wm8770->disable_nb[i]);

	return 0;
}