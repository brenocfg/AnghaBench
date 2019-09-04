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
struct xfrm_if_parms {void* if_id; void* link; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 size_t IFLA_XFRM_IF_ID ; 
 size_t IFLA_XFRM_LINK ; 
 int /*<<< orphan*/  memset (struct xfrm_if_parms*,int /*<<< orphan*/ ,int) ; 
 void* nla_get_u32 (struct nlattr*) ; 

__attribute__((used)) static void xfrmi_netlink_parms(struct nlattr *data[],
			       struct xfrm_if_parms *parms)
{
	memset(parms, 0, sizeof(*parms));

	if (!data)
		return;

	if (data[IFLA_XFRM_LINK])
		parms->link = nla_get_u32(data[IFLA_XFRM_LINK]);

	if (data[IFLA_XFRM_IF_ID])
		parms->if_id = nla_get_u32(data[IFLA_XFRM_IF_ID]);
}