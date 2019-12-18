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
struct TYPE_4__ {scalar_t__ position; scalar_t__ size; int /*<<< orphan*/  blob; } ;
typedef  TYPE_1__ php_stream_sqlite3_data ;
struct TYPE_5__ {int eof; scalar_t__ abstract; } ;
typedef  TYPE_2__ php_stream ;

/* Variables and functions */
 scalar_t__ SQLITE_OK ; 
 scalar_t__ sqlite3_blob_read (int /*<<< orphan*/ ,char*,size_t,size_t) ; 

__attribute__((used)) static ssize_t php_sqlite3_stream_read(php_stream *stream, char *buf, size_t count)
{
	php_stream_sqlite3_data *sqlite3_stream = (php_stream_sqlite3_data *) stream->abstract;

	if (sqlite3_stream->position + count >= sqlite3_stream->size) {
		count = sqlite3_stream->size - sqlite3_stream->position;
		stream->eof = 1;
	}
	if (count) {
		if (sqlite3_blob_read(sqlite3_stream->blob, buf, count, sqlite3_stream->position) != SQLITE_OK) {
			return -1;
		}
		sqlite3_stream->position += count;
	}
	return count;
}