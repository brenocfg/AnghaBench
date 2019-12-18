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
struct nf_logger {int /*<<< orphan*/  me; } ;
typedef  enum nf_log_type { ____Placeholder_nf_log_type } nf_log_type ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int NFPROTO_INET ; 
 int NFPROTO_IPV4 ; 
 int NFPROTO_IPV6 ; 
 int /*<<< orphan*/ *** loggers ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 struct nf_logger* rcu_dereference (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

void nf_logger_put(int pf, enum nf_log_type type)
{
	struct nf_logger *logger;

	if (pf == NFPROTO_INET) {
		nf_logger_put(NFPROTO_IPV4, type);
		nf_logger_put(NFPROTO_IPV6, type);
		return;
	}

	BUG_ON(loggers[pf][type] == NULL);

	rcu_read_lock();
	logger = rcu_dereference(loggers[pf][type]);
	module_put(logger->me);
	rcu_read_unlock();
}