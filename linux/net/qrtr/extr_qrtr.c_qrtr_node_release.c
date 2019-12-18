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
struct qrtr_node {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  __qrtr_node_release ; 
 int /*<<< orphan*/  kref_put_mutex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qrtr_node_lock ; 

__attribute__((used)) static void qrtr_node_release(struct qrtr_node *node)
{
	if (!node)
		return;
	kref_put_mutex(&node->ref, __qrtr_node_release, &qrtr_node_lock);
}