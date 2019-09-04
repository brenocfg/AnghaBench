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
struct nf_logger {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int NF_LOG_TYPE_MAX ; 
 int /*<<< orphan*/ *** loggers ; 
 struct nf_logger* nft_log_dereference (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncasecmp (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nf_logger *__find_logger(int pf, const char *str_logger)
{
	struct nf_logger *log;
	int i;

	for (i = 0; i < NF_LOG_TYPE_MAX; i++) {
		if (loggers[pf][i] == NULL)
			continue;

		log = nft_log_dereference(loggers[pf][i]);
		if (!strncasecmp(str_logger, log->name, strlen(log->name)))
			return log;
	}

	return NULL;
}