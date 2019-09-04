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
struct TYPE_2__ {int /*<<< orphan*/  master; } ;
struct sh_sci_spi {TYPE_1__ bitbang; int /*<<< orphan*/  membase; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIN_INIT ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct sh_sci_spi* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  setbits (struct sh_sci_spi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_bitbang_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  spi_master_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sh_sci_spi_remove(struct platform_device *dev)
{
	struct sh_sci_spi *sp = platform_get_drvdata(dev);

	spi_bitbang_stop(&sp->bitbang);
	setbits(sp, PIN_INIT, 0);
	iounmap(sp->membase);
	spi_master_put(sp->bitbang.master);
	return 0;
}