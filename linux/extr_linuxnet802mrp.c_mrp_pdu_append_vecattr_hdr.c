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
struct mrp_vecattr_hdr {int /*<<< orphan*/  firstattrvalue; int /*<<< orphan*/  lenflags; } ;
struct mrp_applicant {int /*<<< orphan*/  pdu; } ;
struct TYPE_2__ {int /*<<< orphan*/  attrvalue; struct mrp_vecattr_hdr* vah; } ;

/* Variables and functions */
 struct mrp_vecattr_hdr* __skb_put (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,scalar_t__) ; 
 TYPE_1__* mrp_cb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_unaligned (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ skb_tailroom (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mrp_pdu_append_vecattr_hdr(struct mrp_applicant *app,
				      const void *firstattrvalue, u8 attrlen)
{
	struct mrp_vecattr_hdr *vah;

	if (skb_tailroom(app->pdu) < sizeof(*vah) + attrlen)
		return -1;
	vah = __skb_put(app->pdu, sizeof(*vah) + attrlen);
	put_unaligned(0, &vah->lenflags);
	memcpy(vah->firstattrvalue, firstattrvalue, attrlen);
	mrp_cb(app->pdu)->vah = vah;
	memcpy(mrp_cb(app->pdu)->attrvalue, firstattrvalue, attrlen);
	return 0;
}