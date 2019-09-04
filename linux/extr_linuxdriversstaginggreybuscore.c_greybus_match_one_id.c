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
struct greybus_bundle_id {int match_flags; scalar_t__ vendor; scalar_t__ product; scalar_t__ class; } ;
struct gb_bundle {scalar_t__ class; TYPE_1__* intf; } ;
struct TYPE_2__ {scalar_t__ vendor_id; scalar_t__ product_id; } ;

/* Variables and functions */
 int GREYBUS_ID_MATCH_CLASS ; 
 int GREYBUS_ID_MATCH_PRODUCT ; 
 int GREYBUS_ID_MATCH_VENDOR ; 

__attribute__((used)) static bool greybus_match_one_id(struct gb_bundle *bundle,
				     const struct greybus_bundle_id *id)
{
	if ((id->match_flags & GREYBUS_ID_MATCH_VENDOR) &&
	    (id->vendor != bundle->intf->vendor_id))
		return false;

	if ((id->match_flags & GREYBUS_ID_MATCH_PRODUCT) &&
	    (id->product != bundle->intf->product_id))
		return false;

	if ((id->match_flags & GREYBUS_ID_MATCH_CLASS) &&
	    (id->class != bundle->class))
		return false;

	return true;
}