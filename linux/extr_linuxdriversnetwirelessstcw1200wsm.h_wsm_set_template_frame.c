#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wsm_template_frame {TYPE_1__* skb; int /*<<< orphan*/  rate; int /*<<< orphan*/  frame_type; } ;
struct cw1200_common {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_3__ {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  WSM_MIB_ID_TEMPLATE_FRAME ; 
 int /*<<< orphan*/  __cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * skb_push (TYPE_1__*,int) ; 
 int wsm_write_mib (struct cw1200_common*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int wsm_set_template_frame(struct cw1200_common *priv,
					 struct wsm_template_frame *arg)
{
	int ret;
	u8 *p = skb_push(arg->skb, 4);
	p[0] = arg->frame_type;
	p[1] = arg->rate;
	((__le16 *)p)[1] = __cpu_to_le16(arg->skb->len - 4);
	ret = wsm_write_mib(priv, WSM_MIB_ID_TEMPLATE_FRAME, p, arg->skb->len);
	skb_pull(arg->skb, 4);
	return ret;
}