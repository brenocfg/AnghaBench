#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zend_file_handle ;

/* Variables and functions */
 int REPORT_ERRORS ; 
 int STREAM_OPEN_FOR_INCLUDE ; 
 int USE_PATH ; 
 int php_stream_open_for_zend_ex (char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int php_stream_open_for_zend(const char *filename, zend_file_handle *handle) /* {{{ */
{
	return php_stream_open_for_zend_ex(filename, handle, USE_PATH|REPORT_ERRORS|STREAM_OPEN_FOR_INCLUDE);
}