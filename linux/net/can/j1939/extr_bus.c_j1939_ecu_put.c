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
struct j1939_ecu {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  __j1939_ecu_release ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void j1939_ecu_put(struct j1939_ecu *ecu)
{
	kref_put(&ecu->kref, __j1939_ecu_release);
}