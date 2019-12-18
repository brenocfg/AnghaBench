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
struct list_head {int dummy; } ;
struct aa_ns {int dummy; } ;

/* Variables and functions */
 struct aa_ns* __aa_findn_ns (struct list_head*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static inline struct aa_ns *__aa_find_ns(struct list_head *head,
					 const char *name)
{
	return __aa_findn_ns(head, name, strlen(name));
}