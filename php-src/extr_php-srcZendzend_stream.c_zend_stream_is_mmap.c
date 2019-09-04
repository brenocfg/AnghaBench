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
struct TYPE_3__ {scalar_t__ type; } ;
typedef  TYPE_1__ zend_file_handle ;

/* Variables and functions */
 scalar_t__ ZEND_HANDLE_MAPPED ; 

__attribute__((used)) static inline int zend_stream_is_mmap(zend_file_handle *file_handle) { /* {{{ */
	return file_handle->type == ZEND_HANDLE_MAPPED;
}