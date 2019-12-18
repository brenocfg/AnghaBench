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
struct world {int /*<<< orphan*/  root_count; } ;
struct root {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct root*) ; 

__attribute__((used)) static void root_destroy(void *priv, void *root_priv)
{
	struct root *root = root_priv;
	struct world *world = priv;

	world->root_count--;
	kfree(root);
}