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
struct nvme_fc_lport {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int kref_get_unless_zero (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nvme_fc_lport_get(struct nvme_fc_lport *lport)
{
	return kref_get_unless_zero(&lport->ref);
}