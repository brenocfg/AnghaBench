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
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  dim ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_CUR ; 
 unsigned int abs (int /*<<< orphan*/ ) ; 
 scalar_t__ ecalloc (int,int) ; 
 int php_stream_read (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ php_stream_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct gfxinfo *php_handle_bmp (php_stream * stream)
{
	struct gfxinfo *result = NULL;
	unsigned char dim[16];
	int size;

	if (php_stream_seek(stream, 11, SEEK_CUR))
		return NULL;

	if (php_stream_read(stream, (char*)dim, sizeof(dim)) != sizeof(dim))
		return NULL;

	size   = (((unsigned int)dim[ 3]) << 24) + (((unsigned int)dim[ 2]) << 16) + (((unsigned int)dim[ 1]) << 8) + ((unsigned int) dim[ 0]);
	if (size == 12) {
		result = (struct gfxinfo *) ecalloc (1, sizeof(struct gfxinfo));
		result->width    =  (((unsigned int)dim[ 5]) << 8) + ((unsigned int) dim[ 4]);
		result->height   =  (((unsigned int)dim[ 7]) << 8) + ((unsigned int) dim[ 6]);
		result->bits     =  ((unsigned int)dim[11]);
	} else if (size > 12 && (size <= 64 || size == 108 || size == 124)) {
		result = (struct gfxinfo *) ecalloc (1, sizeof(struct gfxinfo));
		result->width    =  (((unsigned int)dim[ 7]) << 24) + (((unsigned int)dim[ 6]) << 16) + (((unsigned int)dim[ 5]) << 8) + ((unsigned int) dim[ 4]);
		result->height   =  (((unsigned int)dim[11]) << 24) + (((unsigned int)dim[10]) << 16) + (((unsigned int)dim[ 9]) << 8) + ((unsigned int) dim[ 8]);
		result->height   =  abs((int32_t)result->height);
		result->bits     =  (((unsigned int)dim[15]) <<  8) +  ((unsigned int)dim[14]);
	} else {
		return NULL;
	}

	return result;
}