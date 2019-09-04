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
typedef  int u32 ;
struct imx_media_pixfmt {int* codes; int fourcc; scalar_t__ bayer; } ;

/* Variables and functions */

__attribute__((used)) static const
struct imx_media_pixfmt *__find_format(u32 fourcc,
				       u32 code,
				       bool allow_non_mbus,
				       bool allow_bayer,
				       const struct imx_media_pixfmt *array,
				       u32 array_size)
{
	const struct imx_media_pixfmt *fmt;
	int i, j;

	for (i = 0; i < array_size; i++) {
		fmt = &array[i];

		if ((!allow_non_mbus && !fmt->codes[0]) ||
		    (!allow_bayer && fmt->bayer))
			continue;

		if (fourcc && fmt->fourcc == fourcc)
			return fmt;

		if (!code)
			continue;

		for (j = 0; fmt->codes[j]; j++) {
			if (code == fmt->codes[j])
				return fmt;
		}
	}
	return NULL;
}