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
struct uwire_spi {int /*<<< orphan*/  bitbang; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct uwire_spi* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  spi_bitbang_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uwire_off (struct uwire_spi*) ; 

__attribute__((used)) static int uwire_remove(struct platform_device *pdev)
{
	struct uwire_spi	*uwire = platform_get_drvdata(pdev);

	// FIXME remove all child devices, somewhere ...

	spi_bitbang_stop(&uwire->bitbang);
	uwire_off(uwire);
	return 0;
}