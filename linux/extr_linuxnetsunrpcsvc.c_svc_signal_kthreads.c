#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct task_struct {int dummy; } ;
struct svc_serv {int sv_nrthreads; } ;
struct svc_pool {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGINT ; 
 struct task_struct* choose_victim (struct svc_serv*,struct svc_pool*,unsigned int*) ; 
 int /*<<< orphan*/  send_sig (int /*<<< orphan*/ ,struct task_struct*,int) ; 

__attribute__((used)) static int
svc_signal_kthreads(struct svc_serv *serv, struct svc_pool *pool, int nrservs)
{
	struct task_struct *task;
	unsigned int state = serv->sv_nrthreads-1;

	/* destroy old threads */
	do {
		task = choose_victim(serv, pool, &state);
		if (task == NULL)
			break;
		send_sig(SIGINT, task, 1);
		nrservs++;
	} while (nrservs < 0);

	return 0;
}