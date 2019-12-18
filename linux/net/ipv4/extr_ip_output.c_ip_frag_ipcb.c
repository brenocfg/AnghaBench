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
struct sk_buff {int dummy; } ;
struct ip_frag_state {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 TYPE_1__* IPCB (struct sk_buff*) ; 
 int /*<<< orphan*/  ip_options_fragment (struct sk_buff*) ; 

__attribute__((used)) static void ip_frag_ipcb(struct sk_buff *from, struct sk_buff *to,
			 bool first_frag, struct ip_frag_state *state)
{
	/* Copy the flags to each fragment. */
	IPCB(to)->flags = IPCB(from)->flags;

	/* ANK: dirty, but effective trick. Upgrade options only if
	 * the segment to be fragmented was THE FIRST (otherwise,
	 * options are already fixed) and make it ONCE
	 * on the initial skb, so that all the following fragments
	 * will inherit fixed options.
	 */
	if (first_frag)
		ip_options_fragment(from);
}