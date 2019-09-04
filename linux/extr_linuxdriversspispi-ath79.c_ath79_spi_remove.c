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
struct platform_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  master; } ;
struct ath79_spi {TYPE_1__ bitbang; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath79_spi_disable (struct ath79_spi*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct ath79_spi* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  spi_bitbang_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  spi_master_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath79_spi_remove(struct platform_device *pdev)
{
	struct ath79_spi *sp = platform_get_drvdata(pdev);

	spi_bitbang_stop(&sp->bitbang);
	ath79_spi_disable(sp);
	clk_disable_unprepare(sp->clk);
	spi_master_put(sp->bitbang.master);

	return 0;
}