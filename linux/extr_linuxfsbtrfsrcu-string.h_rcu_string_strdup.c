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
struct rcu_string {int /*<<< orphan*/  str; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct rcu_string* kzalloc (int,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,size_t) ; 

__attribute__((used)) static inline struct rcu_string *rcu_string_strdup(const char *src, gfp_t mask)
{
	size_t len = strlen(src) + 1;
	struct rcu_string *ret = kzalloc(sizeof(struct rcu_string) +
					 (len * sizeof(char)), mask);
	if (!ret)
		return ret;
	strncpy(ret->str, src, len);
	return ret;
}