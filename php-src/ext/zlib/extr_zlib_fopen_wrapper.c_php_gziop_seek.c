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
typedef  int /*<<< orphan*/  zend_off_t ;
struct php_gz_stream_data_t {int /*<<< orphan*/  gz_file; } ;
struct TYPE_3__ {scalar_t__ abstract; } ;
typedef  TYPE_1__ php_stream ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 int SEEK_END ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gzseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int php_gziop_seek(php_stream *stream, zend_off_t offset, int whence, zend_off_t *newoffs)
{
	struct php_gz_stream_data_t *self = (struct php_gz_stream_data_t *) stream->abstract;

	assert(self != NULL);

	if (whence == SEEK_END) {
		php_error_docref(NULL, E_WARNING, "SEEK_END is not supported");
		return -1;
	}
	*newoffs = gzseek(self->gz_file, offset, whence);

	return (*newoffs < 0) ? -1 : 0;
}