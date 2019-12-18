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
struct vmx_pages {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_vmcs_control_fields (struct vmx_pages*) ; 
 int /*<<< orphan*/  init_vmcs_guest_state (void*,void*) ; 
 int /*<<< orphan*/  init_vmcs_host_state () ; 

void prepare_vmcs(struct vmx_pages *vmx, void *guest_rip, void *guest_rsp)
{
	init_vmcs_control_fields(vmx);
	init_vmcs_host_state();
	init_vmcs_guest_state(guest_rip, guest_rsp);
}