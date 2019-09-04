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
struct michael_mic {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  michael_append (struct michael_mic*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  michael_get_mic (struct michael_mic*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  michael_init (struct michael_mic*,int /*<<< orphan*/ *) ; 

void michael_mic_function(struct michael_mic *mic, u8 *key,
			  u8 *data, unsigned int len, u8 priority, u8 *result)
{
	u8 pad_data[4] = { priority, 0, 0, 0 };
	// Compute the MIC value
	/*
	 * IEEE802.11i  page 47
	 * Figure 43g TKIP MIC processing format
	 * +--+--+--------+--+----+--+--+--+--+--+--+--+--+
	 * |6 |6 |1       |3 |M   |1 |1 |1 |1 |1 |1 |1 |1 | Octet
	 * +--+--+--------+--+----+--+--+--+--+--+--+--+--+
	 * |DA|SA|Priority|0 |Data|M0|M1|M2|M3|M4|M5|M6|M7|
	 * +--+--+--------+--+----+--+--+--+--+--+--+--+--+
	 */
	michael_init(mic, key);
	michael_append(mic, data, 12);	/* |DA|SA| */
	michael_append(mic, pad_data, 4);	/* |Priority|0|0|0| */
	michael_append(mic, data + 12, len - 12);	/* |Data| */
	michael_get_mic(mic, result);
}