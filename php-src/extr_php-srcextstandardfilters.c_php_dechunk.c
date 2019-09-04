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
struct TYPE_3__ {int state; int chunk_size; } ;
typedef  TYPE_1__ php_chunked_filter_data ;

/* Variables and functions */
#define  CHUNK_BODY 137 
#define  CHUNK_BODY_CR 136 
#define  CHUNK_BODY_LF 135 
#define  CHUNK_ERROR 134 
#define  CHUNK_SIZE 133 
#define  CHUNK_SIZE_CR 132 
#define  CHUNK_SIZE_EXT 131 
#define  CHUNK_SIZE_LF 130 
#define  CHUNK_SIZE_START 129 
#define  CHUNK_TRAILER 128 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 

__attribute__((used)) static size_t php_dechunk(char *buf, size_t len, php_chunked_filter_data *data)
{
	char *p = buf;
	char *end = p + len;
	char *out = buf;
	size_t out_len = 0;

	while (p < end) {
		switch (data->state) {
			case CHUNK_SIZE_START:
				data->chunk_size = 0;
			case CHUNK_SIZE:
				while (p < end) {
					if (*p >= '0' && *p <= '9') {
						data->chunk_size = (data->chunk_size * 16) + (*p - '0');
					} else if (*p >= 'A' && *p <= 'F') {
						data->chunk_size = (data->chunk_size * 16) + (*p - 'A' + 10);
					} else if (*p >= 'a' && *p <= 'f') {
						data->chunk_size = (data->chunk_size * 16) + (*p - 'a' + 10);
					} else if (data->state == CHUNK_SIZE_START) {
						data->state = CHUNK_ERROR;
						break;
					} else {
						data->state = CHUNK_SIZE_EXT;
						break;
					}
					data->state = CHUNK_SIZE;
					p++;
				}
				if (data->state == CHUNK_ERROR) {
					continue;
				} else if (p == end) {
					return out_len;
				}
			case CHUNK_SIZE_EXT:
				/* skip extension */
				while (p < end && *p != '\r' && *p != '\n') {
					p++;
				}
				if (p == end) {
					return out_len;
				}
			case CHUNK_SIZE_CR:
				if (*p == '\r') {
					p++;
					if (p == end) {
						data->state = CHUNK_SIZE_LF;
						return out_len;
					}
				}
			case CHUNK_SIZE_LF:
				if (*p == '\n') {
					p++;
					if (data->chunk_size == 0) {
						/* last chunk */
						data->state = CHUNK_TRAILER;
						continue;
					} else if (p == end) {
						data->state = CHUNK_BODY;
						return out_len;
					}
				} else {
					data->state = CHUNK_ERROR;
					continue;
				}
			case CHUNK_BODY:
				if ((size_t) (end - p) >= data->chunk_size) {
					if (p != out) {
						memmove(out, p, data->chunk_size);
					}
					out += data->chunk_size;
					out_len += data->chunk_size;
					p += data->chunk_size;
					if (p == end) {
						data->state = CHUNK_BODY_CR;
						return out_len;
					}
				} else {
					if (p != out) {
						memmove(out, p, end - p);
					}
					data->chunk_size -= end - p;
					data->state=CHUNK_BODY;
					out_len += end - p;
					return out_len;
				}
			case CHUNK_BODY_CR:
				if (*p == '\r') {
					p++;
					if (p == end) {
						data->state = CHUNK_BODY_LF;
						return out_len;
					}
				}
			case CHUNK_BODY_LF:
				if (*p == '\n') {
					p++;
					data->state = CHUNK_SIZE_START;
					continue;
				} else {
					data->state = CHUNK_ERROR;
					continue;
				}
			case CHUNK_TRAILER:
				/* ignore trailer */
				p = end;
				continue;
			case CHUNK_ERROR:
				if (p != out) {
					memmove(out, p, end - p);
				}
				out_len += end - p;
				return out_len;
		}
	}
	return out_len;
}