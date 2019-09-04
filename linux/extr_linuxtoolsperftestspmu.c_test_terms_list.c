#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct list_head {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  list; } ;
typedef  struct list_head LIST_HEAD ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 TYPE_1__* test_terms ; 

__attribute__((used)) static struct list_head *test_terms_list(void)
{
	static LIST_HEAD(terms);
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(test_terms); i++)
		list_add_tail(&test_terms[i].list, &terms);

	return &terms;
}