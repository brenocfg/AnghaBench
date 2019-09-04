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
typedef  scalar_t__ u32 ;
struct bcm2835_codec_fmt {scalar_t__ mmal_fmt; int /*<<< orphan*/  is_bayer; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct bcm2835_codec_fmt const*) ; 
 int /*<<< orphan*/  disable_bayer ; 
 struct bcm2835_codec_fmt const* supported_formats ; 

__attribute__((used)) static const struct bcm2835_codec_fmt *get_fmt(u32 mmal_fmt)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(supported_formats); i++) {
		if (supported_formats[i].mmal_fmt == mmal_fmt &&
		    (!disable_bayer || !supported_formats[i].is_bayer))
			return &supported_formats[i];
	}
	return NULL;
}