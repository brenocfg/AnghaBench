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
struct TYPE_5__ {TYPE_1__* model; } ;
struct TYPE_4__ {int /*<<< orphan*/  cmd; } ;
typedef  TYPE_2__ RPanel ;
typedef  int /*<<< orphan*/  RCore ;

/* Variables and functions */
 char* __show_status_input (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* r_core_cmd_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_str_newf (char*,char*) ; 

char *__load_cmdf(RCore *core, RPanel *p, char *input, char *str) {
	char *ret = NULL;
	char *res = __show_status_input (core, input);
	if (res) {
		p->model->cmd = r_str_newf (str, res);
		ret = r_core_cmd_str (core, p->model->cmd);
		free (res);
	}
	return ret;
}