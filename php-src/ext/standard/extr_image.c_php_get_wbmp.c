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
struct gfxinfo {int width; int height; } ;
typedef  int /*<<< orphan*/  php_stream ;

/* Variables and functions */
 int IMAGE_FILETYPE_WBMP ; 
 int php_stream_getc (int /*<<< orphan*/ *) ; 
 scalar_t__ php_stream_rewind (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int php_get_wbmp(php_stream *stream, struct gfxinfo **result, int check)
{
	int i, width = 0, height = 0;

	if (php_stream_rewind(stream)) {
		return 0;
	}

	/* get type */
	if (php_stream_getc(stream) != 0) {
		return 0;
	}

	/* skip header */
	do {
		i = php_stream_getc(stream);
		if (i < 0) {
			return 0;
		}
	} while (i & 0x80);

	/* get width */
	do {
		i = php_stream_getc(stream);
		if (i < 0) {
			return 0;
		}
		width = (width << 7) | (i & 0x7f);
        /* maximum valid width for wbmp (although 127 may be a more accurate one) */
        if (width > 2048) {
            return 0;
        }
	} while (i & 0x80);

	/* get height */
	do {
		i = php_stream_getc(stream);
		if (i < 0) {
			return 0;
		}
		height = (height << 7) | (i & 0x7f);
        /* maximum valid height for wbmp (although 127 may be a more accurate one) */
        if (height > 2048) {
            return 0;
        }
	} while (i & 0x80);

	if (!height || !width) {
		return 0;
	}

	if (!check) {
		(*result)->width = width;
		(*result)->height = height;
	}

	return IMAGE_FILETYPE_WBMP;
}