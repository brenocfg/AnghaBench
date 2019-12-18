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
struct TYPE_3__ {int /*<<< orphan*/  fp; } ;
typedef  TYPE_1__ inifile ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 int FAILURE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int SUCCESS ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  php_stream_seek (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int php_stream_truncate_set_size (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int inifile_truncate(inifile *dba, size_t size)
{
	int res;

	if ((res=php_stream_truncate_set_size(dba->fp, size)) != 0) {
		php_error_docref(NULL, E_WARNING, "Error in ftruncate: %d", res);
		return FAILURE;
	}
	php_stream_seek(dba->fp, size, SEEK_SET);
	return SUCCESS;
}