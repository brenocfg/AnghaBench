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

/* Variables and functions */
 int /*<<< orphan*/  TID_LIMIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soft_serial_initiator_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transactions ; 

void transport_master_init(void) { soft_serial_initiator_init(transactions, TID_LIMIT(transactions)); }