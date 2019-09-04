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
struct TYPE_2__ {scalar_t__ name; int /*<<< orphan*/  skip_for_len; } ;

/* Variables and functions */
 scalar_t__ strlen (scalar_t__) ; 
 TYPE_1__* txbits ; 

int hist_entry__transaction_len(void)
{
	int i;
	int len = 0;

	for (i = 0; txbits[i].name; i++) {
		if (!txbits[i].skip_for_len)
			len += strlen(txbits[i].name);
	}
	len += 4; /* :XX<space> */
	return len;
}