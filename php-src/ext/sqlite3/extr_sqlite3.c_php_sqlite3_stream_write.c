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
typedef  int ssize_t ;
struct TYPE_4__ {int flags; scalar_t__ position; scalar_t__ size; int /*<<< orphan*/  blob; } ;
typedef  TYPE_1__ php_stream_sqlite3_data ;
struct TYPE_5__ {int eof; scalar_t__ abstract; } ;
typedef  TYPE_2__ php_stream ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 scalar_t__ SQLITE_OK ; 
 int SQLITE_OPEN_READONLY ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ sqlite3_blob_write (int /*<<< orphan*/ ,char const*,size_t,scalar_t__) ; 

__attribute__((used)) static ssize_t php_sqlite3_stream_write(php_stream *stream, const char *buf, size_t count)
{
	php_stream_sqlite3_data *sqlite3_stream = (php_stream_sqlite3_data *) stream->abstract;

	if (sqlite3_stream->flags & SQLITE_OPEN_READONLY) {
		php_error_docref(NULL, E_WARNING, "Can't write to blob stream: is open as read only");
		return -1;
	}

	if (sqlite3_stream->position + count > sqlite3_stream->size) {
		php_error_docref(NULL, E_WARNING, "It is not possible to increase the size of a BLOB");
		return -1;
	}

	if (sqlite3_blob_write(sqlite3_stream->blob, buf, count, sqlite3_stream->position) != SQLITE_OK) {
		return -1;
	}

	if (sqlite3_stream->position + count >= sqlite3_stream->size) {
		stream->eof = 1;
		sqlite3_stream->position = sqlite3_stream->size;
	}
	else {
		sqlite3_stream->position += count;
	}

	return count;
}