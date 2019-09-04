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
typedef  scalar_t__ u8 ;
struct TYPE_2__ {scalar_t__ element_id; } ;
struct ieee_types_vendor_specific {TYPE_1__ vend_hdr; } ;

/* Variables and functions */

__attribute__((used)) static bool
has_vendor_hdr(struct ieee_types_vendor_specific *ie, u8 key)
{
	return (ie && ie->vend_hdr.element_id == key);
}