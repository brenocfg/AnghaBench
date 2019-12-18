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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int FAILURE ; 
 int SUCCESS ; 
 int /*<<< orphan*/ * VCWD_FOPEN (char*,char*) ; 
 int /*<<< orphan*/  php_printf (char*,char*) ; 
 int /*<<< orphan*/  zend_stream_init_fp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int cli_seek_file_begin(zend_file_handle *file_handle, char *script_file)
{
	FILE *fp = VCWD_FOPEN(script_file, "rb");
	if (!fp) {
		php_printf("Could not open input file: %s\n", script_file);
		return FAILURE;
	}

	zend_stream_init_fp(file_handle, fp, script_file);
	return SUCCESS;
}