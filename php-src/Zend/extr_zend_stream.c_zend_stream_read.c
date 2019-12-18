#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t (* reader ) (int /*<<< orphan*/ ,char*,size_t) ;int /*<<< orphan*/  handle; scalar_t__ isatty; } ;
struct TYPE_7__ {TYPE_1__ stream; } ;
struct TYPE_8__ {TYPE_2__ handle; } ;
typedef  TYPE_3__ zend_file_handle ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int EOF ; 
 size_t stub1 (int /*<<< orphan*/ ,char*,size_t) ; 
 int zend_stream_getc (TYPE_3__*) ; 

__attribute__((used)) static ssize_t zend_stream_read(zend_file_handle *file_handle, char *buf, size_t len) /* {{{ */
{
	if (file_handle->handle.stream.isatty) {
		int c = '*';
		size_t n;

		for (n = 0; n < len && (c = zend_stream_getc(file_handle)) != EOF && c != '\n'; ++n)  {
			buf[n] = (char)c;
		}
		if (c == '\n') {
			buf[n++] = (char)c;
		}

		return n;
	}
	return file_handle->handle.stream.reader(file_handle->handle.stream.handle, buf, len);
}