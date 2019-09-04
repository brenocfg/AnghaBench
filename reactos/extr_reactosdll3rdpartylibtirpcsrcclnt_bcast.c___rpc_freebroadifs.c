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
struct broadif {int dummy; } ;
typedef  int /*<<< orphan*/  broadlist_t ;

/* Variables and functions */
 struct broadif* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct broadif* TAILQ_NEXT (struct broadif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct broadif*) ; 
 int /*<<< orphan*/  link ; 

void
__rpc_freebroadifs(broadlist_t *list)
{
	struct broadif *bip, *next;

	bip = TAILQ_FIRST(list);

	while (bip != NULL) {
		next = TAILQ_NEXT(bip, link);
		free(bip);
		bip = next;
	}
}