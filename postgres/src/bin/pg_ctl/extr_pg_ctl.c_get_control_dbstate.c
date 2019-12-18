#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  DBState ;
typedef  TYPE_1__ ControlFileData ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 TYPE_1__* get_controlfile (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 
 int /*<<< orphan*/  pg_data ; 
 int /*<<< orphan*/  progname ; 
 int /*<<< orphan*/  write_stderr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static DBState
get_control_dbstate(void)
{
	DBState		ret;
	bool		crc_ok;
	ControlFileData *control_file_data = get_controlfile(pg_data, &crc_ok);

	if (!crc_ok)
	{
		write_stderr(_("%s: control file appears to be corrupt\n"), progname);
		exit(1);
	}

	ret = control_file_data->state;
	pfree(control_file_data);
	return ret;
}