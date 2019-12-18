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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_genl_family ; 

__attribute__((used)) static inline void *nfc_hdr_put(struct sk_buff *skb, u32 portid, u32 seq,
				int flags, u8 cmd)
{
	/* since there is no private header just add the generic one */
	return genlmsg_put(skb, portid, seq, &nfc_genl_family, flags, cmd);
}