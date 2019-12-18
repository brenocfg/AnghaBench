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
typedef  int const u_int8_t ;
struct tcphdr {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*) ; 
 int* skb_header_pointer (struct sk_buff const*,unsigned int,unsigned int,int const*) ; 

__attribute__((used)) static bool
tcp_find_option(u_int8_t option,
		const struct sk_buff *skb,
		unsigned int protoff,
		unsigned int optlen,
		bool invert,
		bool *hotdrop)
{
	/* tcp.doff is only 4 bits, ie. max 15 * 4 bytes */
	const u_int8_t *op;
	u_int8_t _opt[60 - sizeof(struct tcphdr)];
	unsigned int i;

	pr_debug("finding option\n");

	if (!optlen)
		return invert;

	/* If we don't have the whole header, drop packet. */
	op = skb_header_pointer(skb, protoff + sizeof(struct tcphdr),
				optlen, _opt);
	if (op == NULL) {
		*hotdrop = true;
		return false;
	}

	for (i = 0; i < optlen; ) {
		if (op[i] == option) return !invert;
		if (op[i] < 2) i++;
		else i += op[i+1]?:1;
	}

	return invert;
}