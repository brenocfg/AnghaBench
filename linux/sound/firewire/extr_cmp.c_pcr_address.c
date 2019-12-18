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
typedef  scalar_t__ u64 ;
struct cmp_connection {scalar_t__ direction; int /*<<< orphan*/  pcr_index; } ;

/* Variables and functions */
 scalar_t__ CMP_INPUT ; 
 scalar_t__ CSR_IPCR (int /*<<< orphan*/ ) ; 
 scalar_t__ CSR_OPCR (int /*<<< orphan*/ ) ; 
 scalar_t__ CSR_REGISTER_BASE ; 

__attribute__((used)) static u64 pcr_address(struct cmp_connection *c)
{
	if (c->direction == CMP_INPUT)
		return CSR_REGISTER_BASE + CSR_IPCR(c->pcr_index);
	else
		return CSR_REGISTER_BASE + CSR_OPCR(c->pcr_index);
}