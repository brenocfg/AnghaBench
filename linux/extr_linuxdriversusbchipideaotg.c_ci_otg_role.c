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
struct ci_hdrc {int dummy; } ;
typedef  enum ci_role { ____Placeholder_ci_role } ci_role ;

/* Variables and functions */
 int CI_ROLE_GADGET ; 
 int CI_ROLE_HOST ; 
 int /*<<< orphan*/  OTGSC_ID ; 
 scalar_t__ hw_read_otgsc (struct ci_hdrc*,int /*<<< orphan*/ ) ; 

enum ci_role ci_otg_role(struct ci_hdrc *ci)
{
	enum ci_role role = hw_read_otgsc(ci, OTGSC_ID)
		? CI_ROLE_GADGET
		: CI_ROLE_HOST;

	return role;
}