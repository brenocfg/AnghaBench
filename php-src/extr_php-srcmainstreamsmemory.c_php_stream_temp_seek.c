#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int zend_off_t ;
struct TYPE_6__ {TYPE_4__* innerstream; } ;
typedef  TYPE_1__ php_stream_temp_data ;
struct TYPE_7__ {int /*<<< orphan*/  eof; scalar_t__ abstract; } ;
typedef  TYPE_2__ php_stream ;
struct TYPE_8__ {int /*<<< orphan*/  eof; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int php_stream_seek (TYPE_4__*,int,int) ; 
 int php_stream_tell (TYPE_4__*) ; 

__attribute__((used)) static int php_stream_temp_seek(php_stream *stream, zend_off_t offset, int whence, zend_off_t *newoffs)
{
	php_stream_temp_data *ts = (php_stream_temp_data*)stream->abstract;
	int ret;

	assert(ts != NULL);

	if (!ts->innerstream) {
		*newoffs = -1;
		return -1;
	}
	ret = php_stream_seek(ts->innerstream, offset, whence);
	*newoffs = php_stream_tell(ts->innerstream);
	stream->eof = ts->innerstream->eof;

	return ret;
}