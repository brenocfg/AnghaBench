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
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  sa; int /*<<< orphan*/  da; int /*<<< orphan*/  src_name; int /*<<< orphan*/  dst_name; } ;
struct j1939_sk_buff_cb {int flags; TYPE_1__ addr; } ;

/* Variables and functions */
 int J1939_ECU_LOCAL_DST ; 
 int J1939_ECU_LOCAL_SRC ; 
 int /*<<< orphan*/  swap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void j1939_skbcb_swap(struct j1939_sk_buff_cb *skcb)
{
	u8 tmp = 0;

	swap(skcb->addr.dst_name, skcb->addr.src_name);
	swap(skcb->addr.da, skcb->addr.sa);

	/* swap SRC and DST flags, leave other untouched */
	if (skcb->flags & J1939_ECU_LOCAL_SRC)
		tmp |= J1939_ECU_LOCAL_DST;
	if (skcb->flags & J1939_ECU_LOCAL_DST)
		tmp |= J1939_ECU_LOCAL_SRC;
	skcb->flags &= ~(J1939_ECU_LOCAL_SRC | J1939_ECU_LOCAL_DST);
	skcb->flags |= tmp;
}