#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_off_t ;
struct TYPE_14__ {TYPE_2__* innerstream; } ;
typedef  TYPE_1__ php_stream_temp_data ;
struct TYPE_15__ {scalar_t__ abstract; } ;
typedef  TYPE_2__ php_stream ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 int FAILURE ; 
 int PHP_STREAM_AS_STDIO ; 
 int /*<<< orphan*/  PHP_STREAM_FREE_CLOSE ; 
 int /*<<< orphan*/  PHP_STREAM_IS_STDIO ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int SUCCESS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int php_stream_cast (TYPE_2__*,int,void**,int) ; 
 int /*<<< orphan*/  php_stream_encloses (TYPE_2__*,TYPE_2__*) ; 
 TYPE_2__* php_stream_fopen_tmpfile () ; 
 int /*<<< orphan*/  php_stream_free_enclosed (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ php_stream_is (TYPE_2__*,int /*<<< orphan*/ ) ; 
 char* php_stream_memory_get_buffer (TYPE_2__*,size_t*) ; 
 int /*<<< orphan*/  php_stream_seek (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_stream_tell (TYPE_2__*) ; 
 int /*<<< orphan*/  php_stream_write (TYPE_2__*,char*,size_t) ; 

__attribute__((used)) static int php_stream_temp_cast(php_stream *stream, int castas, void **ret)
{
	php_stream_temp_data *ts = (php_stream_temp_data*)stream->abstract;
	php_stream *file;
	size_t memsize;
	char *membuf;
	zend_off_t pos;

	assert(ts != NULL);

	if (!ts->innerstream) {
		return FAILURE;
	}
	if (php_stream_is(ts->innerstream, PHP_STREAM_IS_STDIO)) {
		return php_stream_cast(ts->innerstream, castas, ret, 0);
	}

	/* we are still using a memory based backing. If they are if we can be
	 * a FILE*, say yes because we can perform the conversion.
	 * If they actually want to perform the conversion, we need to switch
	 * the memory stream to a tmpfile stream */

	if (ret == NULL && castas == PHP_STREAM_AS_STDIO) {
		return SUCCESS;
	}

	/* say "no" to other stream forms */
	if (ret == NULL) {
		return FAILURE;
	}

	file = php_stream_fopen_tmpfile();
	if (file == NULL) {
		php_error_docref(NULL, E_WARNING, "Unable to create temporary file.");
		return FAILURE;
	}

	/* perform the conversion and then pass the request on to the innerstream */
	membuf = php_stream_memory_get_buffer(ts->innerstream, &memsize);
	php_stream_write(file, membuf, memsize);
	pos = php_stream_tell(ts->innerstream);

	php_stream_free_enclosed(ts->innerstream, PHP_STREAM_FREE_CLOSE);
	ts->innerstream = file;
	php_stream_encloses(stream, ts->innerstream);
	php_stream_seek(ts->innerstream, pos, SEEK_SET);

	return php_stream_cast(ts->innerstream, castas, ret, 1);
}