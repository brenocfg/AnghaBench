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
struct deferred_export {int /*<<< orphan*/  node; struct comm* comm; } ;
struct db_export {int /*<<< orphan*/  deferred; } ;
struct comm {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct deferred_export* zalloc (int) ; 

__attribute__((used)) static int db_export__defer_comm(struct db_export *dbe, struct comm *comm)
{
	struct deferred_export *de;

	de = zalloc(sizeof(struct deferred_export));
	if (!de)
		return -ENOMEM;

	de->comm = comm;
	list_add_tail(&de->node, &dbe->deferred);

	return 0;
}