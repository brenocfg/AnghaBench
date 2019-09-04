#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  php_stream ;
struct TYPE_5__ {int readonly; int /*<<< orphan*/ * fp; } ;
typedef  TYPE_1__ inifile ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* pemalloc (int,int) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  php_stream_truncate_supported (int /*<<< orphan*/ *) ; 

inifile * inifile_alloc(php_stream *fp, int readonly, int persistent)
{
	inifile *dba;

	if (!readonly) {
		if (!php_stream_truncate_supported(fp)) {
			php_error_docref(NULL, E_WARNING, "Can't truncate this stream");
			return NULL;
		}
	}

	dba = pemalloc(sizeof(inifile), persistent);
	memset(dba, 0, sizeof(inifile));
	dba->fp = fp;
	dba->readonly = readonly;
	return dba;
}