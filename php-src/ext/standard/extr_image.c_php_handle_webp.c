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
struct gfxinfo {unsigned char width; unsigned char height; int bits; } ;
typedef  int /*<<< orphan*/  php_stream ;

/* Variables and functions */
 scalar_t__ ecalloc (int,int) ; 
 scalar_t__ memcmp (unsigned char*,char const*,int) ; 
 int php_stream_read (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static struct gfxinfo *php_handle_webp(php_stream * stream)
{
	struct gfxinfo *result = NULL;
	const char sig[3] = {'V', 'P', '8'};
	unsigned char buf[18];
	char format;

	if (php_stream_read(stream, (char *) buf, 18) != 18)
		return NULL;

	if (memcmp(buf, sig, 3)) {
		return NULL;
	}
	switch (buf[3]) {
		case ' ':
		case 'L':
		case 'X':
			format = buf[3];
			break;
		default:
			return NULL;
	}

	result = (struct gfxinfo *) ecalloc(1, sizeof(struct gfxinfo));

	switch (format) {
		case ' ':
			result->width = buf[14] + ((buf[15] & 0x3F) << 8);
			result->height = buf[16] + ((buf[17] & 0x3F) << 8);
			break;
		case 'L':
			result->width = buf[9] + ((buf[10] & 0x3F) << 8) + 1;
			result->height = (buf[10] >> 6) + (buf[11] << 2) + ((buf[12] & 0xF) << 10) + 1;
			break;
		case 'X':
			result->width = buf[12] + (buf[13] << 8) + (buf[14] << 16) + 1;
			result->height = buf[15] + (buf[16] << 8) + (buf[17] << 16) + 1;
			break;
	}
	result->bits = 8; /* always 1 byte */

	return result;
}