#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ zend_stream_reader_t ;
struct TYPE_5__ {int /*<<< orphan*/ * closer; scalar_t__ isatty; int /*<<< orphan*/ * fsizer; scalar_t__ reader; int /*<<< orphan*/ * handle; } ;
struct TYPE_6__ {TYPE_1__ stream; } ;
struct TYPE_7__ {char* filename; char* buf; size_t len; int /*<<< orphan*/  type; TYPE_2__ handle; int /*<<< orphan*/ * opened_path; scalar_t__ free_filename; } ;
typedef  TYPE_3__ zend_file_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ZEND_HANDLE_STREAM ; 
 scalar_t__ _php_stream_read ; 
 int fuzzer_do_request (TYPE_3__*,char*) ; 

int fuzzer_do_request_from_buffer(char *filename, char *data, size_t data_len)
{
	zend_file_handle file_handle;
	file_handle.filename = filename;
	file_handle.free_filename = 0;
	file_handle.opened_path = NULL;
	file_handle.handle.stream.handle = NULL;
	file_handle.handle.stream.reader = (zend_stream_reader_t)_php_stream_read;
	file_handle.handle.stream.fsizer = NULL;
	file_handle.handle.stream.isatty = 0;
	file_handle.handle.stream.closer   = NULL;
	file_handle.buf = data;
	file_handle.len = data_len;
	file_handle.type = ZEND_HANDLE_STREAM;

	return fuzzer_do_request(&file_handle, filename);
}