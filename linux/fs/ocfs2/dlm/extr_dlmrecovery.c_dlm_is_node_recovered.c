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
typedef  int /*<<< orphan*/  u8 ;
struct dlm_ctxt {int /*<<< orphan*/  spinlock; int /*<<< orphan*/  recovery_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dlm_is_node_recovered(struct dlm_ctxt *dlm, u8 node)
{
	int recovered;
	spin_lock(&dlm->spinlock);
	recovered = !test_bit(node, dlm->recovery_map);
	spin_unlock(&dlm->spinlock);
	return recovered;
}