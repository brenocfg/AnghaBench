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
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int nla_put_u16 (struct sk_buff*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nla_put_shortaddr(struct sk_buff *msg, int type, __le16 addr)
{
	return nla_put_u16(msg, type, le16_to_cpu(addr));
}