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
struct ff_codec_desc {int type; } ;
typedef  enum ff_codec_type { ____Placeholder_ff_codec_type } ff_codec_type ;

/* Variables and functions */
 int FF_CODEC_UNKNOWN ; 

enum ff_codec_type ff_codec_desc_type(const struct ff_codec_desc *codec_desc)
{
	if (codec_desc != NULL)
		return codec_desc->type;
	else
		return FF_CODEC_UNKNOWN;
}