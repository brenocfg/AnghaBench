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
struct TYPE_5__ {struct TYPE_5__* tmpdir; int /*<<< orphan*/  meta; scalar_t__ innerstream; } ;
typedef  TYPE_1__ php_stream_temp_data ;
struct TYPE_6__ {scalar_t__ abstract; } ;
typedef  TYPE_2__ php_stream ;

/* Variables and functions */
 int PHP_STREAM_FREE_CLOSE ; 
 int PHP_STREAM_FREE_PRESERVE_HANDLE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efree (TYPE_1__*) ; 
 int php_stream_free_enclosed (scalar_t__,int) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int php_stream_temp_close(php_stream *stream, int close_handle)
{
	php_stream_temp_data *ts = (php_stream_temp_data*)stream->abstract;
	int ret;

	assert(ts != NULL);

	if (ts->innerstream) {
		ret = php_stream_free_enclosed(ts->innerstream, PHP_STREAM_FREE_CLOSE | (close_handle ? 0 : PHP_STREAM_FREE_PRESERVE_HANDLE));
	} else {
		ret = 0;
	}

	zval_ptr_dtor(&ts->meta);

	if (ts->tmpdir) {
		efree(ts->tmpdir);
	}

	efree(ts);

	return ret;
}