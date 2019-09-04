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
struct fl_flow_tmplt {int /*<<< orphan*/  chain; } ;

/* Variables and functions */
 int /*<<< orphan*/  fl_hw_destroy_tmplt (int /*<<< orphan*/ ,struct fl_flow_tmplt*) ; 
 int /*<<< orphan*/  kfree (struct fl_flow_tmplt*) ; 

__attribute__((used)) static void fl_tmplt_destroy(void *tmplt_priv)
{
	struct fl_flow_tmplt *tmplt = tmplt_priv;

	fl_hw_destroy_tmplt(tmplt->chain, tmplt);
	kfree(tmplt);
}