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
struct c67x00_td {int /*<<< orphan*/  td_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct c67x00_td*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void c67x00_release_td(struct c67x00_td *td)
{
	list_del_init(&td->td_list);
	kfree(td);
}