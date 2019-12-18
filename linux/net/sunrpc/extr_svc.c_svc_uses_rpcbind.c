#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct svc_serv {struct svc_program* sv_program; } ;
struct svc_program {unsigned int pg_nvers; TYPE_1__** pg_vers; struct svc_program* pg_next; } ;
struct TYPE_2__ {int /*<<< orphan*/  vs_hidden; } ;

/* Variables and functions */

__attribute__((used)) static int svc_uses_rpcbind(struct svc_serv *serv)
{
	struct svc_program	*progp;
	unsigned int		i;

	for (progp = serv->sv_program; progp; progp = progp->pg_next) {
		for (i = 0; i < progp->pg_nvers; i++) {
			if (progp->pg_vers[i] == NULL)
				continue;
			if (!progp->pg_vers[i]->vs_hidden)
				return 1;
		}
	}

	return 0;
}