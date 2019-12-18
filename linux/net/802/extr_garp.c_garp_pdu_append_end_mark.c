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
typedef  int /*<<< orphan*/  u8 ;
struct garp_applicant {int /*<<< orphan*/  pdu; } ;

/* Variables and functions */
 int /*<<< orphan*/  GARP_END_MARK ; 
 int /*<<< orphan*/  __skb_put_u8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int skb_tailroom (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int garp_pdu_append_end_mark(struct garp_applicant *app)
{
	if (skb_tailroom(app->pdu) < sizeof(u8))
		return -1;
	__skb_put_u8(app->pdu, GARP_END_MARK);
	return 0;
}