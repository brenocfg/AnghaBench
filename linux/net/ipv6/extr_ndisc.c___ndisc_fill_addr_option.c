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
typedef  int u8 ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int __ndisc_opt_addr_space (int,int) ; 
 int /*<<< orphan*/  memcpy (int*,void*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int* skb_put (struct sk_buff*,int) ; 

void __ndisc_fill_addr_option(struct sk_buff *skb, int type, void *data,
			      int data_len, int pad)
{
	int space = __ndisc_opt_addr_space(data_len, pad);
	u8 *opt = skb_put(skb, space);

	opt[0] = type;
	opt[1] = space>>3;

	memset(opt + 2, 0, pad);
	opt   += pad;
	space -= pad;

	memcpy(opt+2, data, data_len);
	data_len += 2;
	opt += data_len;
	space -= data_len;
	if (space > 0)
		memset(opt, 0, space);
}