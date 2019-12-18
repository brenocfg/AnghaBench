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
struct TYPE_5__ {size_t (* fsizer ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  handle; scalar_t__ isatty; } ;
struct TYPE_6__ {TYPE_1__ stream; } ;
struct TYPE_7__ {scalar_t__ type; TYPE_2__ handle; } ;
typedef  TYPE_3__ zend_file_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ZEND_ASSERT (int) ; 
 scalar_t__ ZEND_HANDLE_STREAM ; 
 size_t stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t zend_stream_fsize(zend_file_handle *file_handle) /* {{{ */
{
	ZEND_ASSERT(file_handle->type == ZEND_HANDLE_STREAM);
	if (file_handle->handle.stream.isatty) {
		return 0;
	}
	return file_handle->handle.stream.fsizer(file_handle->handle.stream.handle);
}