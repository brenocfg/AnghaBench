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
struct TYPE_2__ {int* gpcs; int /*<<< orphan*/ * gpio; } ;
struct zoran {TYPE_1__ card; } ;

/* Variables and functions */
 size_t GPCS_JPEG_RESET ; 
 int /*<<< orphan*/  GPIO (struct zoran*,int /*<<< orphan*/ ,int) ; 
 size_t ZR_GPIO_JPEG_RESET ; 
 int /*<<< orphan*/  jpeg_codec_sleep (struct zoran*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  post_office_write (struct zoran*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

int
jpeg_codec_reset (struct zoran *zr)
{
	/* Take the codec out of sleep */
	jpeg_codec_sleep(zr, 0);

	if (zr->card.gpcs[GPCS_JPEG_RESET] != 0xff) {
		post_office_write(zr, zr->card.gpcs[GPCS_JPEG_RESET], 0,
				  0);
		udelay(2);
	} else {
		GPIO(zr, zr->card.gpio[ZR_GPIO_JPEG_RESET], 0);
		udelay(2);
		GPIO(zr, zr->card.gpio[ZR_GPIO_JPEG_RESET], 1);
		udelay(2);
	}

	return 0;
}