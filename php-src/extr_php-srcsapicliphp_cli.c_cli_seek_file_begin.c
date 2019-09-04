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
typedef  scalar_t__ zend_long ;
struct TYPE_4__ {int /*<<< orphan*/  fp; } ;
struct TYPE_5__ {char* filename; TYPE_1__ handle; scalar_t__ free_filename; int /*<<< orphan*/ * opened_path; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ zend_file_handle ;

/* Variables and functions */
 int EOF ; 
 int FAILURE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int SUCCESS ; 
 int /*<<< orphan*/  VCWD_FOPEN (char*,char*) ; 
 int /*<<< orphan*/  ZEND_HANDLE_FP ; 
 char fgetc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_printf (char*,char*) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_fseek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ zend_ftell (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cli_seek_file_begin(zend_file_handle *file_handle, char *script_file, int *lineno)
{
	int c;

	*lineno = 1;

	file_handle->type = ZEND_HANDLE_FP;
	file_handle->opened_path = NULL;
	file_handle->free_filename = 0;
	if (!(file_handle->handle.fp = VCWD_FOPEN(script_file, "rb"))) {
		php_printf("Could not open input file: %s\n", script_file);
		return FAILURE;
	}
	file_handle->filename = script_file;

	/* #!php support */
	c = fgetc(file_handle->handle.fp);
	if (c == '#' && (c = fgetc(file_handle->handle.fp)) == '!') {
		while (c != '\n' && c != '\r' && c != EOF) {
			c = fgetc(file_handle->handle.fp);	/* skip to end of line */
		}
		/* handle situations where line is terminated by \r\n */
		if (c == '\r') {
			if (fgetc(file_handle->handle.fp) != '\n') {
				zend_long pos = zend_ftell(file_handle->handle.fp);
				zend_fseek(file_handle->handle.fp, pos - 1, SEEK_SET);
			}
		}
		*lineno = 2;
	} else {
		rewind(file_handle->handle.fp);
	}

	return SUCCESS;
}