#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct unix_address {TYPE_1__* name; scalar_t__ len; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  sun_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNIX_DIAG_NAME ; 
 int nla_put (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct unix_address* smp_load_acquire (int /*<<< orphan*/ *) ; 
 TYPE_2__* unix_sk (struct sock*) ; 

__attribute__((used)) static int sk_diag_dump_name(struct sock *sk, struct sk_buff *nlskb)
{
	/* might or might not have unix_table_lock */
	struct unix_address *addr = smp_load_acquire(&unix_sk(sk)->addr);

	if (!addr)
		return 0;

	return nla_put(nlskb, UNIX_DIAG_NAME, addr->len - sizeof(short),
		       addr->name->sun_path);
}