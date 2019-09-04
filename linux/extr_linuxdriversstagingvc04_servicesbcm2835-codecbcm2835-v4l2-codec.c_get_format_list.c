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
struct bcm2835_codec_fmt_list {int dummy; } ;
struct bcm2835_codec_dev {struct bcm2835_codec_fmt_list* supported_fmts; } ;

/* Variables and functions */

__attribute__((used)) static inline
struct bcm2835_codec_fmt_list *get_format_list(struct bcm2835_codec_dev *dev,
					       bool capture)
{
	return &dev->supported_fmts[capture ? 1 : 0];
}