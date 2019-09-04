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
struct sock {int dummy; } ;
struct sk_msg_buff {int /*<<< orphan*/  sg_end; int /*<<< orphan*/  sg_start; } ;

/* Variables and functions */
 int free_sg (struct sock*,int /*<<< orphan*/ ,struct sk_msg_buff*,int) ; 

__attribute__((used)) static int free_start_sg(struct sock *sk, struct sk_msg_buff *md, bool charge)
{
	int free = free_sg(sk, md->sg_start, md, charge);

	md->sg_start = md->sg_end;
	return free;
}