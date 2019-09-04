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
struct bcm2835_codec_fmt {int dummy; } ;
struct bcm2835_codec_dev {TYPE_1__* supported_fmts; } ;
struct TYPE_2__ {struct bcm2835_codec_fmt* list; } ;

/* Variables and functions */

__attribute__((used)) static
struct bcm2835_codec_fmt *get_default_format(struct bcm2835_codec_dev *dev,
					     bool capture)
{
	return &dev->supported_fmts[capture ? 1 : 0].list[0];
}