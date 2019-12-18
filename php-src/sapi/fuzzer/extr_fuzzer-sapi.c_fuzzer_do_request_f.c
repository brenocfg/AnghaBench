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
struct TYPE_4__ {int /*<<< orphan*/ * fp; } ;
struct TYPE_5__ {char* filename; int /*<<< orphan*/ * opened_path; TYPE_1__ handle; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ zend_file_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ZEND_HANDLE_FILENAME ; 
 int fuzzer_do_request (TYPE_2__*,char*) ; 

int fuzzer_do_request_f(char *filename)
{
	zend_file_handle file_handle;
	file_handle.type = ZEND_HANDLE_FILENAME;
	file_handle.filename = filename;
	file_handle.handle.fp = NULL;
	file_handle.opened_path = NULL;

	return fuzzer_do_request(&file_handle, filename);
}