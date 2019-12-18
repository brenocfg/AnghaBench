#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * p; } ;
struct extended_perms {int len; TYPE_2__ drivers; } ;
struct TYPE_12__ {int specified; } ;
struct TYPE_10__ {TYPE_3__* xperms; } ;
struct TYPE_11__ {TYPE_4__ u; } ;
struct avtab_node {TYPE_6__ key; TYPE_5__ datum; } ;
struct TYPE_7__ {int /*<<< orphan*/ * p; } ;
struct TYPE_9__ {scalar_t__ specified; int /*<<< orphan*/  driver; TYPE_1__ perms; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int AVTAB_XPERMS_ALLOWED ; 
 scalar_t__ AVTAB_XPERMS_IOCTLDRIVER ; 
 scalar_t__ AVTAB_XPERMS_IOCTLFUNCTION ; 
 int /*<<< orphan*/  security_xperm_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void services_compute_xperms_drivers(
		struct extended_perms *xperms,
		struct avtab_node *node)
{
	unsigned int i;

	if (node->datum.u.xperms->specified == AVTAB_XPERMS_IOCTLDRIVER) {
		/* if one or more driver has all permissions allowed */
		for (i = 0; i < ARRAY_SIZE(xperms->drivers.p); i++)
			xperms->drivers.p[i] |= node->datum.u.xperms->perms.p[i];
	} else if (node->datum.u.xperms->specified == AVTAB_XPERMS_IOCTLFUNCTION) {
		/* if allowing permissions within a driver */
		security_xperm_set(xperms->drivers.p,
					node->datum.u.xperms->driver);
	}

	/* If no ioctl commands are allowed, ignore auditallow and auditdeny */
	if (node->key.specified & AVTAB_XPERMS_ALLOWED)
		xperms->len = 1;
}