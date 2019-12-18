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
struct mrp_applicant {int /*<<< orphan*/  pdu; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  MRP_END_MARK ; 
 int /*<<< orphan*/ * __skb_put (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_unaligned (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int skb_tailroom (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mrp_pdu_append_end_mark(struct mrp_applicant *app)
{
	__be16 *endmark;

	if (skb_tailroom(app->pdu) < sizeof(*endmark))
		return -1;
	endmark = __skb_put(app->pdu, sizeof(*endmark));
	put_unaligned(MRP_END_MARK, endmark);
	return 0;
}