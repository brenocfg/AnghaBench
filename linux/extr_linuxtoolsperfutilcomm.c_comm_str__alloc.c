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
struct comm_str {int /*<<< orphan*/  refcnt; int /*<<< orphan*/  str; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct comm_str*) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strdup (char const*) ; 
 struct comm_str* zalloc (int) ; 

__attribute__((used)) static struct comm_str *comm_str__alloc(const char *str)
{
	struct comm_str *cs;

	cs = zalloc(sizeof(*cs));
	if (!cs)
		return NULL;

	cs->str = strdup(str);
	if (!cs->str) {
		free(cs);
		return NULL;
	}

	refcount_set(&cs->refcnt, 1);

	return cs;
}