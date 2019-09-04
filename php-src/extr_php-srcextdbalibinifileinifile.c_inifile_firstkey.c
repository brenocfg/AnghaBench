#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ pos; } ;
struct TYPE_5__ {TYPE_3__ curr; } ;
typedef  TYPE_1__ inifile ;

/* Variables and functions */
 int /*<<< orphan*/  inifile_line_free (TYPE_3__*) ; 
 int inifile_nextkey (TYPE_1__*) ; 

int inifile_firstkey(inifile *dba) {
	inifile_line_free(&dba->curr);
	dba->curr.pos = 0;
	return inifile_nextkey(dba);
}