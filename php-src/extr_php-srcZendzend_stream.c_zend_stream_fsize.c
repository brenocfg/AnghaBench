#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {size_t st_size; } ;
typedef  TYPE_4__ zend_stat_t ;
struct TYPE_9__ {size_t len; } ;
struct TYPE_10__ {size_t (* fsizer ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  handle; TYPE_1__ mmap; } ;
struct TYPE_11__ {scalar_t__ fp; TYPE_2__ stream; } ;
struct TYPE_13__ {scalar_t__ type; TYPE_3__ handle; } ;
typedef  TYPE_5__ zend_file_handle ;

/* Variables and functions */
 scalar_t__ ZEND_HANDLE_MAPPED ; 
 scalar_t__ ZEND_HANDLE_STREAM ; 
 int /*<<< orphan*/  fileno (scalar_t__) ; 
 size_t stub1 (int /*<<< orphan*/ ) ; 
 scalar_t__ zend_fstat (int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ zend_stream_is_mmap (TYPE_5__*) ; 

__attribute__((used)) static size_t zend_stream_fsize(zend_file_handle *file_handle) /* {{{ */
{
	zend_stat_t buf;

	if (zend_stream_is_mmap(file_handle)) {
		return file_handle->handle.stream.mmap.len;
	}
	if (file_handle->type == ZEND_HANDLE_STREAM || file_handle->type == ZEND_HANDLE_MAPPED) {
		return file_handle->handle.stream.fsizer(file_handle->handle.stream.handle);
	}
	if (file_handle->handle.fp && zend_fstat(fileno(file_handle->handle.fp), &buf) == 0) {
#ifdef S_ISREG
		if (!S_ISREG(buf.st_mode)) {
			return 0;
		}
#endif
		return buf.st_size;
	}

	return -1;
}