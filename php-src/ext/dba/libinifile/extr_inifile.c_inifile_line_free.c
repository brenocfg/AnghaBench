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
struct TYPE_3__ {scalar_t__ pos; int /*<<< orphan*/  val; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ line_type ;

/* Variables and functions */
 int /*<<< orphan*/  inifile_key_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inifile_val_free (int /*<<< orphan*/ *) ; 

void inifile_line_free(line_type *ln)
{
	inifile_key_free(&ln->key);
	inifile_val_free(&ln->val);
	ln->pos = 0;
}