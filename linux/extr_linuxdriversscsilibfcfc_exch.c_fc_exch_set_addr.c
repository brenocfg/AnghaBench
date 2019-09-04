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
typedef  void* u32 ;
struct fc_exch {int esb_stat; void* did; void* sid; void* oid; } ;

/* Variables and functions */
 int ESB_ST_RESP ; 

__attribute__((used)) static void fc_exch_set_addr(struct fc_exch *ep,
			     u32 orig_id, u32 resp_id)
{
	ep->oid = orig_id;
	if (ep->esb_stat & ESB_ST_RESP) {
		ep->sid = resp_id;
		ep->did = orig_id;
	} else {
		ep->sid = orig_id;
		ep->did = resp_id;
	}
}