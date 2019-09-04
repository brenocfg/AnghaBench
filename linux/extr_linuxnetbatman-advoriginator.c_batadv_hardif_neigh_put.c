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
struct batadv_hardif_neigh_node {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  batadv_hardif_neigh_release ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void batadv_hardif_neigh_put(struct batadv_hardif_neigh_node *hardif_neigh)
{
	kref_put(&hardif_neigh->refcount, batadv_hardif_neigh_release);
}