#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t avail_in; size_t avail_out; int /*<<< orphan*/ * next_out; } ;
typedef  TYPE_1__ z_stream ;
struct TYPE_6__ {size_t size; size_t used; char* aptr; char* data; size_t free; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_2__ php_zlib_buffer ;
typedef  int /*<<< orphan*/  Bytef ;

/* Variables and functions */
 int Z_BUF_ERROR ; 
 int Z_DATA_ERROR ; 
 int Z_MEM_ERROR ; 
 int /*<<< orphan*/  Z_NO_FLUSH ; 
 int Z_OK ; 
 int Z_STREAM_END ; 
 int /*<<< orphan*/  efree (char*) ; 
 char* erealloc (char*,int) ; 
 char* erealloc_recoverable (char*,size_t) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,size_t,size_t,size_t,size_t,size_t) ; 
 int inflate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static inline int php_zlib_inflate_rounds(z_stream *Z, size_t max, char **buf, size_t *len)
{
	int status, round = 0;
	php_zlib_buffer buffer = {NULL, NULL, 0, 0, 0};

	*buf = NULL;
	*len = 0;

	buffer.size = (max && (max < Z->avail_in)) ? max : Z->avail_in;

	do {
		if ((max && (max <= buffer.used)) || !(buffer.aptr = erealloc_recoverable(buffer.data, buffer.size))) {
			status = Z_MEM_ERROR;
		} else {
			buffer.data = buffer.aptr;
			Z->avail_out = buffer.free = buffer.size - buffer.used;
			Z->next_out = (Bytef *) buffer.data + buffer.used;
#if 0
			fprintf(stderr, "\n%3d: %3d PRIOR: size=%7lu,\tfree=%7lu,\tused=%7lu,\tavail_in=%7lu,\tavail_out=%7lu\n", round, status, buffer.size, buffer.free, buffer.used, Z->avail_in, Z->avail_out);
#endif
			status = inflate(Z, Z_NO_FLUSH);

			buffer.used += buffer.free - Z->avail_out;
			buffer.free = Z->avail_out;
#if 0
			fprintf(stderr, "%3d: %3d AFTER: size=%7lu,\tfree=%7lu,\tused=%7lu,\tavail_in=%7lu,\tavail_out=%7lu\n", round, status, buffer.size, buffer.free, buffer.used, Z->avail_in, Z->avail_out);
#endif
			buffer.size += (buffer.size >> 3) + 1;
		}
	} while ((Z_BUF_ERROR == status || (Z_OK == status && Z->avail_in)) && ++round < 100);

	if (status == Z_STREAM_END) {
		buffer.data = erealloc(buffer.data, buffer.used + 1);
		buffer.data[buffer.used] = '\0';
		*buf = buffer.data;
		*len = buffer.used;
	} else {
		if (buffer.data) {
			efree(buffer.data);
		}
		/* HACK: See zlib/examples/zpipe.c inf() function for explanation. */
		/* This works as long as this function is not used for streaming. Required to catch very short invalid data. */
		status = (status == Z_OK) ? Z_DATA_ERROR : status;
	}
	return status;
}