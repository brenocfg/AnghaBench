#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int ssize_t ;
struct TYPE_11__ {size_t smax; TYPE_2__* innerstream; int /*<<< orphan*/  tmpdir; } ;
typedef  TYPE_1__ php_stream_temp_data ;
struct TYPE_12__ {scalar_t__ abstract; } ;
typedef  TYPE_2__ php_stream ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 int /*<<< orphan*/  PHP_STREAM_FREE_CLOSE ; 
 int /*<<< orphan*/  PHP_STREAM_IS_MEMORY ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  php_stream_encloses (TYPE_2__*,TYPE_2__*) ; 
 TYPE_2__* php_stream_fopen_temporary_file (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_stream_free_enclosed (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ php_stream_is (TYPE_2__*,int /*<<< orphan*/ ) ; 
 char* php_stream_memory_get_buffer (TYPE_2__*,size_t*) ; 
 int php_stream_write (TYPE_2__*,char const*,size_t) ; 

__attribute__((used)) static ssize_t php_stream_temp_write(php_stream *stream, const char *buf, size_t count)
{
	php_stream_temp_data *ts = (php_stream_temp_data*)stream->abstract;
	assert(ts != NULL);

	if (!ts->innerstream) {
		return -1;
	}
	if (php_stream_is(ts->innerstream, PHP_STREAM_IS_MEMORY)) {
		size_t memsize;
		char *membuf = php_stream_memory_get_buffer(ts->innerstream, &memsize);

		if (memsize + count >= ts->smax) {
			php_stream *file = php_stream_fopen_temporary_file(ts->tmpdir, "php", NULL);
			if (file == NULL) {
				php_error_docref(NULL, E_WARNING, "Unable to create temporary file, Check permissions in temporary files directory.");
				return 0;
			}
			php_stream_write(file, membuf, memsize);
			php_stream_free_enclosed(ts->innerstream, PHP_STREAM_FREE_CLOSE);
			ts->innerstream = file;
			php_stream_encloses(stream, ts->innerstream);
		}
	}
	return php_stream_write(ts->innerstream, buf, count);
}