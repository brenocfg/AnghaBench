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
struct gfxinfo {unsigned int width; unsigned int height; unsigned int bits; } ;
typedef  int /*<<< orphan*/  php_stream ;
typedef  int /*<<< orphan*/  dim ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_CUR ; 
 scalar_t__ ecalloc (int,int) ; 
 int php_stream_read (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ php_stream_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct gfxinfo *php_handle_png (php_stream * stream)
{
	struct gfxinfo *result = NULL;
	unsigned char dim[9];
/* Width:              4 bytes
 * Height:             4 bytes
 * Bit depth:          1 byte
 * Color type:         1 byte
 * Compression method: 1 byte
 * Filter method:      1 byte
 * Interlace method:   1 byte
 */

	if (php_stream_seek(stream, 8, SEEK_CUR))
		return NULL;

	if((php_stream_read(stream, (char*)dim, sizeof(dim))) < sizeof(dim))
		return NULL;

	result = (struct gfxinfo *) ecalloc(1, sizeof(struct gfxinfo));
	result->width  = (((unsigned int)dim[0]) << 24) + (((unsigned int)dim[1]) << 16) + (((unsigned int)dim[2]) << 8) + ((unsigned int)dim[3]);
	result->height = (((unsigned int)dim[4]) << 24) + (((unsigned int)dim[5]) << 16) + (((unsigned int)dim[6]) << 8) + ((unsigned int)dim[7]);
	result->bits   = (unsigned int)dim[8];
	return result;
}