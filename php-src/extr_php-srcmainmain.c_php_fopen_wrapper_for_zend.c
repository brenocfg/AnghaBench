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
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int IGNORE_URL_WIN ; 
 int REPORT_ERRORS ; 
 int STREAM_OPEN_FOR_INCLUDE ; 
 int USE_PATH ; 
 int /*<<< orphan*/ * php_stream_open_wrapper_as_file (char*,char*,int,int /*<<< orphan*/ **) ; 

__attribute__((used)) static FILE *php_fopen_wrapper_for_zend(const char *filename, zend_string **opened_path)
{
	return php_stream_open_wrapper_as_file((char *)filename, "rb", USE_PATH|IGNORE_URL_WIN|REPORT_ERRORS|STREAM_OPEN_FOR_INCLUDE, opened_path);
}