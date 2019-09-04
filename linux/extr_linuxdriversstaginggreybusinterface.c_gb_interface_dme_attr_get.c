#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct gb_interface {int /*<<< orphan*/  interface_id; TYPE_1__* hd; } ;
struct TYPE_2__ {int /*<<< orphan*/  svc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DME_SELECTOR_INDEX_NULL ; 
 int gb_svc_dme_peer_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gb_interface_dme_attr_get(struct gb_interface *intf,
				     u16 attr, u32 *val)
{
	return gb_svc_dme_peer_get(intf->hd->svc, intf->interface_id,
					attr, DME_SELECTOR_INDEX_NULL, val);
}