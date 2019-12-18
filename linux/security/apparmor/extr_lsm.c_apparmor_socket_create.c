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
struct aa_label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AA_MAY_CREATE ; 
 int /*<<< orphan*/  OP_CREATE ; 
 int /*<<< orphan*/  aa_af_perm (struct aa_label*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int af_select (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct aa_label* begin_current_label_crit_section () ; 
 int /*<<< orphan*/  create_perm (struct aa_label*,int,int,int) ; 
 int /*<<< orphan*/  end_current_label_crit_section (struct aa_label*) ; 
 int /*<<< orphan*/  in_interrupt () ; 
 scalar_t__ unconfined (struct aa_label*) ; 

__attribute__((used)) static int apparmor_socket_create(int family, int type, int protocol, int kern)
{
	struct aa_label *label;
	int error = 0;

	AA_BUG(in_interrupt());

	label = begin_current_label_crit_section();
	if (!(kern || unconfined(label)))
		error = af_select(family,
				  create_perm(label, family, type, protocol),
				  aa_af_perm(label, OP_CREATE, AA_MAY_CREATE,
					     family, type, protocol));
	end_current_label_crit_section(label);

	return error;
}