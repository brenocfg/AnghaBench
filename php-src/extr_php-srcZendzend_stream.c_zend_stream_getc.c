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
struct TYPE_5__ {int /*<<< orphan*/  handle; scalar_t__ (* reader ) (int /*<<< orphan*/ ,char*,int) ;} ;
struct TYPE_6__ {TYPE_1__ stream; } ;
struct TYPE_7__ {TYPE_2__ handle; } ;
typedef  TYPE_3__ zend_file_handle ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int EOF ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int zend_stream_getc(zend_file_handle *file_handle) /* {{{ */
{
	char buf;

	if (file_handle->handle.stream.reader(file_handle->handle.stream.handle, &buf, sizeof(buf))) {
		return (int)buf;
	}
	return EOF;
}