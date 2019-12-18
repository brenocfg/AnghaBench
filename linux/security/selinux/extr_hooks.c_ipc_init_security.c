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
typedef  int /*<<< orphan*/  u16 ;
struct ipc_security_struct {int /*<<< orphan*/  sid; int /*<<< orphan*/  sclass; } ;

/* Variables and functions */
 int /*<<< orphan*/  current_sid () ; 

__attribute__((used)) static void ipc_init_security(struct ipc_security_struct *isec, u16 sclass)
{
	isec->sclass = sclass;
	isec->sid = current_sid();
}