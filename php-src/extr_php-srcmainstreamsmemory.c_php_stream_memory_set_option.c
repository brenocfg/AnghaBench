#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int mode; size_t fsize; size_t fpos; size_t data; } ;
typedef  TYPE_1__ php_stream_memory_data ;
struct TYPE_5__ {scalar_t__ abstract; } ;
typedef  TYPE_2__ php_stream ;

/* Variables and functions */
 int PHP_STREAM_OPTION_RETURN_ERR ; 
 int PHP_STREAM_OPTION_RETURN_NOTIMPL ; 
 int PHP_STREAM_OPTION_RETURN_OK ; 
#define  PHP_STREAM_OPTION_TRUNCATE_API 130 
#define  PHP_STREAM_TRUNCATE_SET_SIZE 129 
#define  PHP_STREAM_TRUNCATE_SUPPORTED 128 
 int TEMP_STREAM_READONLY ; 
 size_t erealloc (size_t,size_t) ; 
 int /*<<< orphan*/  memset (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int php_stream_memory_set_option(php_stream *stream, int option, int value, void *ptrparam) /* {{{ */
{
	php_stream_memory_data *ms = (php_stream_memory_data*)stream->abstract;
	size_t newsize;

	switch(option) {
		case PHP_STREAM_OPTION_TRUNCATE_API:
			switch (value) {
				case PHP_STREAM_TRUNCATE_SUPPORTED:
					return PHP_STREAM_OPTION_RETURN_OK;

				case PHP_STREAM_TRUNCATE_SET_SIZE:
					if (ms->mode & TEMP_STREAM_READONLY) {
						return PHP_STREAM_OPTION_RETURN_ERR;
					}
					newsize = *(size_t*)ptrparam;
					if (newsize <= ms->fsize) {
						if (newsize < ms->fpos) {
							ms->fpos = newsize;
						}
					} else {
						ms->data = erealloc(ms->data, newsize);
						memset(ms->data+ms->fsize, 0, newsize - ms->fsize);
						ms->fsize = newsize;
					}
					ms->fsize = newsize;
					return PHP_STREAM_OPTION_RETURN_OK;
			}
		default:
			return PHP_STREAM_OPTION_RETURN_NOTIMPL;
	}
}