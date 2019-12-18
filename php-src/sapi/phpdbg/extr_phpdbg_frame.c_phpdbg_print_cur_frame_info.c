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

/* Variables and functions */
 int /*<<< orphan*/  efree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phpdbg_list_file (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 char* zend_get_executed_filename () ; 
 scalar_t__ zend_get_executed_lineno () ; 
 int /*<<< orphan*/ * zend_string_init (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void phpdbg_print_cur_frame_info() {
	const char *file_chr = zend_get_executed_filename();
	zend_string *file = zend_string_init(file_chr, strlen(file_chr), 0);

	phpdbg_list_file(file, 3, zend_get_executed_lineno() - 1, zend_get_executed_lineno());
	efree(file);
}