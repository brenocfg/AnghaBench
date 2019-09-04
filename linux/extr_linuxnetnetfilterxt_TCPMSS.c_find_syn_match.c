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
struct xt_tcp {int flg_cmp; int invflags; } ;
struct TYPE_5__ {TYPE_1__* match; } ;
struct TYPE_6__ {TYPE_2__ kernel; } ;
struct xt_entry_match {TYPE_3__ u; scalar_t__ data; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int TCPHDR_SYN ; 
 int XT_TCP_INV_FLAGS ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static inline bool find_syn_match(const struct xt_entry_match *m)
{
	const struct xt_tcp *tcpinfo = (const struct xt_tcp *)m->data;

	if (strcmp(m->u.kernel.match->name, "tcp") == 0 &&
	    tcpinfo->flg_cmp & TCPHDR_SYN &&
	    !(tcpinfo->invflags & XT_TCP_INV_FLAGS))
		return true;

	return false;
}