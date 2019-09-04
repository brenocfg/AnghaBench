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
struct TYPE_5__ {int /*<<< orphan*/  blob; } ;
typedef  TYPE_1__ php_stream_sqlite3_data ;
struct TYPE_6__ {scalar_t__ abstract; } ;
typedef  TYPE_2__ php_stream ;

/* Variables and functions */
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  efree (TYPE_1__*) ; 
 scalar_t__ sqlite3_blob_close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int php_sqlite3_stream_close(php_stream *stream, int close_handle)
{
	php_stream_sqlite3_data *sqlite3_stream = (php_stream_sqlite3_data *) stream->abstract;

	if (sqlite3_blob_close(sqlite3_stream->blob) != SQLITE_OK) {
		/* Error occurred, but it still closed */
	}

	efree(sqlite3_stream);

	return 0;
}