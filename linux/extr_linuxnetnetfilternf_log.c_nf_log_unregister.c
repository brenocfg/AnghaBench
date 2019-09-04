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
typedef  struct nf_logger {size_t type; } const nf_logger ;

/* Variables and functions */
 int NFPROTO_NUMPROTO ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** loggers ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_log_mutex ; 
 struct nf_logger const* nft_log_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

void nf_log_unregister(struct nf_logger *logger)
{
	const struct nf_logger *log;
	int i;

	mutex_lock(&nf_log_mutex);
	for (i = 0; i < NFPROTO_NUMPROTO; i++) {
		log = nft_log_dereference(loggers[i][logger->type]);
		if (log == logger)
			RCU_INIT_POINTER(loggers[i][logger->type], NULL);
	}
	mutex_unlock(&nf_log_mutex);
	synchronize_rcu();
}