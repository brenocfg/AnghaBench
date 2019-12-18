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
 int ENOENT ; 
 int NFPROTO_INET ; 
 int NFPROTO_IPV4 ; 
 int NFPROTO_IPV6 ; 
 int /*<<< orphan*/ ** loggers ; 
 int /*<<< orphan*/  nf_logger_put (int,int) ; 
 int /*<<< orphan*/ * rcu_access_pointer (int /*<<< orphan*/ ) ; 
 struct nf_logger* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  request_module (char*,int,int) ; 
 scalar_t__ try_module_get (int /*<<< orphan*/ ) ; 

int nf_logger_find_get(int pf, enum nf_log_type type)
{
	struct nf_logger *logger;
	int ret = -ENOENT;

	if (pf == NFPROTO_INET) {
		ret = nf_logger_find_get(NFPROTO_IPV4, type);
		if (ret < 0)
			return ret;

		ret = nf_logger_find_get(NFPROTO_IPV6, type);
		if (ret < 0) {
			nf_logger_put(NFPROTO_IPV4, type);
			return ret;
		}

		return 0;
	}

	if (rcu_access_pointer(loggers[pf][type]) == NULL)
		request_module("nf-logger-%u-%u", pf, type);

	rcu_read_lock();
	logger = rcu_dereference(loggers[pf][type]);
	if (logger == NULL)
		goto out;

	if (try_module_get(logger->me))
		ret = 0;
out:
	rcu_read_unlock();
	return ret;
}