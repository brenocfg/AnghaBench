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
struct ff_codec_desc {char const* long_name; } ;

/* Variables and functions */

const char *ff_codec_desc_long_name(const struct ff_codec_desc *codec_desc)
{
	if (codec_desc != NULL)
		return codec_desc->long_name;
	else
		return NULL;
}