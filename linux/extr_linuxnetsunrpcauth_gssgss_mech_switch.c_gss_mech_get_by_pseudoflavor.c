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
typedef  int /*<<< orphan*/  u32 ;
struct gss_api_mech {int dummy; } ;

/* Variables and functions */
 struct gss_api_mech* _gss_mech_get_by_pseudoflavor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_module (char*,int /*<<< orphan*/ ) ; 

struct gss_api_mech *
gss_mech_get_by_pseudoflavor(u32 pseudoflavor)
{
	struct gss_api_mech *gm;

	gm = _gss_mech_get_by_pseudoflavor(pseudoflavor);

	if (!gm) {
		request_module("rpc-auth-gss-%u", pseudoflavor);
		gm = _gss_mech_get_by_pseudoflavor(pseudoflavor);
	}
	return gm;
}