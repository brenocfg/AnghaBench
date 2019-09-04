#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_1__* model; TYPE_2__* view; } ;
struct TYPE_10__ {int n_panels; } ;
struct TYPE_9__ {int refresh; } ;
struct TYPE_8__ {int /*<<< orphan*/ * cmdStrCache; int /*<<< orphan*/  cmd; } ;
typedef  TYPE_3__ RPanels ;
typedef  TYPE_4__ RPanel ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 TYPE_4__* getPanel (TYPE_3__*,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void setRefreshByType(RPanels *panels, const char *cmd, bool clearCache) {
	int i;
	for (i = 0; i < panels->n_panels; i++) {
		RPanel *p = getPanel (panels, i);
		if (strcmp (p->model->cmd, cmd)) {
			continue;
		}
		p->view->refresh = true;
		if (clearCache) {
			free (p->model->cmdStrCache);
			p->model->cmdStrCache = NULL;
		}
	}
}