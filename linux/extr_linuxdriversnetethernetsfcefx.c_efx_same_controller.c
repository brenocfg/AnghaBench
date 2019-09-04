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
struct efx_nic {scalar_t__ type; scalar_t__ vpd_sn; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (scalar_t__,scalar_t__) ; 

__attribute__((used)) static bool efx_same_controller(struct efx_nic *left, struct efx_nic *right)
{
	return left->type == right->type &&
		left->vpd_sn && right->vpd_sn &&
		!strcmp(left->vpd_sn, right->vpd_sn);
}