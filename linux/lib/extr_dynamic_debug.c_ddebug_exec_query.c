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
struct ddebug_query {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int MAXWORDS ; 
 int ddebug_change (struct ddebug_query*,unsigned int,unsigned int) ; 
 scalar_t__ ddebug_parse_flags (char*,unsigned int*,unsigned int*) ; 
 scalar_t__ ddebug_parse_query (char**,int,struct ddebug_query*,char const*) ; 
 int ddebug_tokenize (char*,char**,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  vpr_info_dq (struct ddebug_query*,char*) ; 

__attribute__((used)) static int ddebug_exec_query(char *query_string, const char *modname)
{
	unsigned int flags = 0, mask = 0;
	struct ddebug_query query;
#define MAXWORDS 9
	int nwords, nfound;
	char *words[MAXWORDS];

	nwords = ddebug_tokenize(query_string, words, MAXWORDS);
	if (nwords <= 0) {
		pr_err("tokenize failed\n");
		return -EINVAL;
	}
	/* check flags 1st (last arg) so query is pairs of spec,val */
	if (ddebug_parse_flags(words[nwords-1], &flags, &mask)) {
		pr_err("flags parse failed\n");
		return -EINVAL;
	}
	if (ddebug_parse_query(words, nwords-1, &query, modname)) {
		pr_err("query parse failed\n");
		return -EINVAL;
	}
	/* actually go and implement the change */
	nfound = ddebug_change(&query, flags, mask);
	vpr_info_dq(&query, nfound ? "applied" : "no-match");

	return nfound;
}