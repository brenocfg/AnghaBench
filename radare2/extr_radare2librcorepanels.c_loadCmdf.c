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
 int /*<<< orphan*/  free (char*) ; 
 char* r_cons_input (char*) ; 
 char* r_core_cmd_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_str_newf (char*,char*) ; 

__attribute__((used)) static char *loadCmdf(RCore *core, RPanel *p, char *input, char *str) {
	char *ret = NULL;
	char *res = r_cons_input (input);
	if (res) {
		p->model->cmd = r_str_newf (str, res);
		ret = r_core_cmd_str (core, p->model->cmd);
		free (res);
	}
	return ret;
}