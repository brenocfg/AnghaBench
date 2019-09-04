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
struct nf_logger {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * nf_loggers; } ;
struct net {TYPE_1__ nf; } ;

/* Variables and functions */
 int NFPROTO_NUMPROTO ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_log_mutex ; 
 struct nf_logger* nft_log_dereference (int /*<<< orphan*/ ) ; 

void nf_log_unset(struct net *net, const struct nf_logger *logger)
{
	int i;
	const struct nf_logger *log;

	mutex_lock(&nf_log_mutex);
	for (i = 0; i < NFPROTO_NUMPROTO; i++) {
		log = nft_log_dereference(net->nf.nf_loggers[i]);
		if (log == logger)
			RCU_INIT_POINTER(net->nf.nf_loggers[i], NULL);
	}
	mutex_unlock(&nf_log_mutex);
}