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
typedef  size_t u_int8_t ;
struct nf_logger {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * nf_loggers; } ;
struct net {TYPE_1__ nf; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EOPNOTSUPP ; 
 size_t NFPROTO_UNSPEC ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_log_mutex ; 
 struct nf_logger* nft_log_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct nf_logger const*) ; 

int nf_log_set(struct net *net, u_int8_t pf, const struct nf_logger *logger)
{
	const struct nf_logger *log;

	if (pf == NFPROTO_UNSPEC || pf >= ARRAY_SIZE(net->nf.nf_loggers))
		return -EOPNOTSUPP;

	mutex_lock(&nf_log_mutex);
	log = nft_log_dereference(net->nf.nf_loggers[pf]);
	if (log == NULL)
		rcu_assign_pointer(net->nf.nf_loggers[pf], logger);

	mutex_unlock(&nf_log_mutex);

	return 0;
}