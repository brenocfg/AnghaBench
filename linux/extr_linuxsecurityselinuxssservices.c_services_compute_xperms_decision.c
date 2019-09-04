#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct extended_perms_decision {scalar_t__ driver; TYPE_4__* dontaudit; int /*<<< orphan*/  used; TYPE_2__* auditallow; TYPE_1__* allowed; } ;
struct TYPE_15__ {TYPE_6__* xperms; } ;
struct TYPE_16__ {TYPE_7__ u; } ;
struct TYPE_11__ {scalar_t__ specified; } ;
struct avtab_node {TYPE_8__ datum; TYPE_3__ key; } ;
struct TYPE_13__ {int /*<<< orphan*/ * p; } ;
struct TYPE_14__ {scalar_t__ specified; scalar_t__ driver; TYPE_5__ perms; } ;
struct TYPE_12__ {int /*<<< orphan*/ * p; } ;
struct TYPE_10__ {int /*<<< orphan*/ * p; } ;
struct TYPE_9__ {int /*<<< orphan*/ * p; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ AVTAB_XPERMS_ALLOWED ; 
 scalar_t__ AVTAB_XPERMS_AUDITALLOW ; 
 scalar_t__ AVTAB_XPERMS_DONTAUDIT ; 
 scalar_t__ AVTAB_XPERMS_IOCTLDRIVER ; 
 scalar_t__ AVTAB_XPERMS_IOCTLFUNCTION ; 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  XPERMS_ALLOWED ; 
 int /*<<< orphan*/  XPERMS_AUDITALLOW ; 
 int /*<<< orphan*/  XPERMS_DONTAUDIT ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  security_xperm_test (int /*<<< orphan*/ *,scalar_t__) ; 

void services_compute_xperms_decision(struct extended_perms_decision *xpermd,
					struct avtab_node *node)
{
	unsigned int i;

	if (node->datum.u.xperms->specified == AVTAB_XPERMS_IOCTLFUNCTION) {
		if (xpermd->driver != node->datum.u.xperms->driver)
			return;
	} else if (node->datum.u.xperms->specified == AVTAB_XPERMS_IOCTLDRIVER) {
		if (!security_xperm_test(node->datum.u.xperms->perms.p,
					xpermd->driver))
			return;
	} else {
		BUG();
	}

	if (node->key.specified == AVTAB_XPERMS_ALLOWED) {
		xpermd->used |= XPERMS_ALLOWED;
		if (node->datum.u.xperms->specified == AVTAB_XPERMS_IOCTLDRIVER) {
			memset(xpermd->allowed->p, 0xff,
					sizeof(xpermd->allowed->p));
		}
		if (node->datum.u.xperms->specified == AVTAB_XPERMS_IOCTLFUNCTION) {
			for (i = 0; i < ARRAY_SIZE(xpermd->allowed->p); i++)
				xpermd->allowed->p[i] |=
					node->datum.u.xperms->perms.p[i];
		}
	} else if (node->key.specified == AVTAB_XPERMS_AUDITALLOW) {
		xpermd->used |= XPERMS_AUDITALLOW;
		if (node->datum.u.xperms->specified == AVTAB_XPERMS_IOCTLDRIVER) {
			memset(xpermd->auditallow->p, 0xff,
					sizeof(xpermd->auditallow->p));
		}
		if (node->datum.u.xperms->specified == AVTAB_XPERMS_IOCTLFUNCTION) {
			for (i = 0; i < ARRAY_SIZE(xpermd->auditallow->p); i++)
				xpermd->auditallow->p[i] |=
					node->datum.u.xperms->perms.p[i];
		}
	} else if (node->key.specified == AVTAB_XPERMS_DONTAUDIT) {
		xpermd->used |= XPERMS_DONTAUDIT;
		if (node->datum.u.xperms->specified == AVTAB_XPERMS_IOCTLDRIVER) {
			memset(xpermd->dontaudit->p, 0xff,
					sizeof(xpermd->dontaudit->p));
		}
		if (node->datum.u.xperms->specified == AVTAB_XPERMS_IOCTLFUNCTION) {
			for (i = 0; i < ARRAY_SIZE(xpermd->dontaudit->p); i++)
				xpermd->dontaudit->p[i] |=
					node->datum.u.xperms->perms.p[i];
		}
	} else {
		BUG();
	}
}