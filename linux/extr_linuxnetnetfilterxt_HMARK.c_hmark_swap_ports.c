#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
union hmark_ports {int b32; int v32; TYPE_1__ b16; } ;
typedef  int u16 ;
struct TYPE_6__ {int b32; } ;
struct TYPE_5__ {int b32; } ;
struct xt_hmark_info {TYPE_3__ port_set; TYPE_2__ port_mask; } ;

/* Variables and functions */
 int ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void hmark_swap_ports(union hmark_ports *uports,
				    const struct xt_hmark_info *info)
{
	union hmark_ports hp;
	u16 src, dst;

	hp.b32 = (uports->b32 & info->port_mask.b32) | info->port_set.b32;
	src = ntohs(hp.b16.src);
	dst = ntohs(hp.b16.dst);

	if (dst > src)
		uports->v32 = (dst << 16) | src;
	else
		uports->v32 = (src << 16) | dst;
}