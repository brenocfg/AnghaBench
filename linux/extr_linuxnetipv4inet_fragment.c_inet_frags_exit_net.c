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
struct netns_frags {int /*<<< orphan*/  rhashtable; scalar_t__ high_thresh; } ;

/* Variables and functions */
 int /*<<< orphan*/  inet_frags_free_cb ; 
 int /*<<< orphan*/  rhashtable_free_and_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void inet_frags_exit_net(struct netns_frags *nf)
{
	nf->high_thresh = 0; /* prevent creation of new frags */

	rhashtable_free_and_destroy(&nf->rhashtable, inet_frags_free_cb, NULL);
}