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
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRC_F_INIT ; 
 int /*<<< orphan*/  crc_itu_t ; 
 int /*<<< orphan*/  digital_skb_add_crc (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void digital_skb_add_crc_f(struct sk_buff *skb)
{
	digital_skb_add_crc(skb, crc_itu_t, CRC_F_INIT, 0, 1);
}