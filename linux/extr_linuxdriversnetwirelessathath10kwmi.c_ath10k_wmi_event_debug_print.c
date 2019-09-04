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
struct sk_buff {int len; char* data; } ;
struct ath10k {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI_PRINT ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 scalar_t__ isascii (char) ; 
 scalar_t__ isprint (char) ; 

void ath10k_wmi_event_debug_print(struct ath10k *ar, struct sk_buff *skb)
{
	char buf[101], c;
	int i;

	for (i = 0; i < sizeof(buf) - 1; i++) {
		if (i >= skb->len)
			break;

		c = skb->data[i];

		if (c == '\0')
			break;

		if (isascii(c) && isprint(c))
			buf[i] = c;
		else
			buf[i] = '.';
	}

	if (i == sizeof(buf) - 1)
		ath10k_warn(ar, "wmi debug print truncated: %d\n", skb->len);

	/* for some reason the debug prints end with \n, remove that */
	if (skb->data[i - 1] == '\n')
		i--;

	/* the last byte is always reserved for the null character */
	buf[i] = '\0';

	ath10k_dbg(ar, ATH10K_DBG_WMI_PRINT, "wmi print '%s'\n", buf);
}