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
struct shrinker {int dummy; } ;
struct shrink_control {int /*<<< orphan*/  nid; } ;
struct pglist_data {int /*<<< orphan*/  split_queue_len; } ;

/* Variables and functions */
 struct pglist_data* NODE_DATA (int /*<<< orphan*/ ) ; 
 unsigned long READ_ONCE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long deferred_split_count(struct shrinker *shrink,
		struct shrink_control *sc)
{
	struct pglist_data *pgdata = NODE_DATA(sc->nid);
	return READ_ONCE(pgdata->split_queue_len);
}