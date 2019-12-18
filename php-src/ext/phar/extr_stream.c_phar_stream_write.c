#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ zend_off_t ;
typedef  int ssize_t ;
struct TYPE_8__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  wrapper; scalar_t__ abstract; } ;
typedef  TYPE_3__ php_stream ;
struct TYPE_9__ {scalar_t__ position; TYPE_2__* internal_file; int /*<<< orphan*/  fp; TYPE_1__* phar; } ;
typedef  TYPE_4__ phar_entry_data ;
struct TYPE_7__ {scalar_t__ uncompressed_filesize; scalar_t__ compressed_filesize; int is_modified; int /*<<< orphan*/  flags; int /*<<< orphan*/  old_flags; int /*<<< orphan*/  filename; } ;
struct TYPE_6__ {int /*<<< orphan*/  fname; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  php_stream_seek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ php_stream_tell (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_stream_wrapper_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t php_stream_write (int /*<<< orphan*/ ,char const*,size_t) ; 

__attribute__((used)) static ssize_t phar_stream_write(php_stream *stream, const char *buf, size_t count) /* {{{ */
{
	phar_entry_data *data = (phar_entry_data *) stream->abstract;

	php_stream_seek(data->fp, data->position, SEEK_SET);
	if (count != php_stream_write(data->fp, buf, count)) {
		php_stream_wrapper_log_error(stream->wrapper, stream->flags, "phar error: Could not write %d characters to \"%s\" in phar \"%s\"", (int) count, data->internal_file->filename, data->phar->fname);
		return -1;
	}
	data->position = php_stream_tell(data->fp);
	if (data->position > (zend_off_t)data->internal_file->uncompressed_filesize) {
		data->internal_file->uncompressed_filesize = data->position;
	}
	data->internal_file->compressed_filesize = data->internal_file->uncompressed_filesize;
	data->internal_file->old_flags = data->internal_file->flags;
	data->internal_file->is_modified = 1;
	return count;
}