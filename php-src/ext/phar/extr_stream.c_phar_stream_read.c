#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ zend_off_t ;
typedef  int ssize_t ;
struct TYPE_7__ {int eof; scalar_t__ abstract; } ;
typedef  TYPE_1__ php_stream ;
struct TYPE_8__ {scalar_t__ uncompressed_filesize; scalar_t__ is_deleted; scalar_t__ link; } ;
typedef  TYPE_2__ phar_entry_info ;
struct TYPE_9__ {scalar_t__ position; scalar_t__ zero; int /*<<< orphan*/  fp; TYPE_2__* internal_file; } ;
typedef  TYPE_3__ phar_entry_data ;

/* Variables and functions */
 int /*<<< orphan*/  MIN (size_t,size_t) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 TYPE_2__* phar_get_link_source (TYPE_2__*) ; 
 size_t php_stream_read (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_stream_seek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ php_stream_tell (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t phar_stream_read(php_stream *stream, char *buf, size_t count) /* {{{ */
{
	phar_entry_data *data = (phar_entry_data *)stream->abstract;
	size_t got;
	phar_entry_info *entry;

	if (data->internal_file->link) {
		entry = phar_get_link_source(data->internal_file);
	} else {
		entry = data->internal_file;
	}

	if (entry->is_deleted) {
		stream->eof = 1;
		return -1;
	}

	/* use our proxy position */
	php_stream_seek(data->fp, data->position + data->zero, SEEK_SET);

	got = php_stream_read(data->fp, buf, MIN(count, (size_t)(entry->uncompressed_filesize - data->position)));
	data->position = php_stream_tell(data->fp) - data->zero;
	stream->eof = (data->position == (zend_off_t) entry->uncompressed_filesize);

	return got;
}