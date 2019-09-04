#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* mode; } ;
typedef  TYPE_1__ php_stream ;

/* Variables and functions */

void php_stream_mode_sanitize_fdopen_fopencookie(php_stream *stream, char *result)
{
	/* replace modes not supported by fdopen and fopencookie, but supported
	 * by PHP's fread(), so that their calls won't fail */
	const char *cur_mode = stream->mode;
	int         has_plus = 0,
		        has_bin  = 0,
				i,
				res_curs = 0;

	if (cur_mode[0] == 'r' || cur_mode[0] == 'w' || cur_mode[0] == 'a') {
		result[res_curs++] = cur_mode[0];
	} else {
		/* assume cur_mode[0] is 'c' or 'x'; substitute by 'w', which should not
		 * truncate anything in fdopen/fopencookie */
		result[res_curs++] = 'w';

		/* x is allowed (at least by glibc & compat), but not as the 1st mode
		 * as in PHP and in any case is (at best) ignored by fdopen and fopencookie */
	}

	/* assume current mode has at most length 4 (e.g. wbn+) */
	for (i = 1; i < 4 && cur_mode[i] != '\0'; i++) {
		if (cur_mode[i] == 'b') {
			has_bin = 1;
		} else if (cur_mode[i] == '+') {
			has_plus = 1;
		}
		/* ignore 'n', 't' or other stuff */
	}

	if (has_bin) {
		result[res_curs++] = 'b';
	}
	if (has_plus) {
		result[res_curs++] = '+';
	}

	result[res_curs] = '\0';
}