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
struct htb_class {scalar_t__ cmode; int /*<<< orphan*/  buffer; } ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
 scalar_t__ HTB_CAN_SEND ; 
 scalar_t__ htb_hysteresis ; 

__attribute__((used)) static inline s64 htb_hiwater(const struct htb_class *cl)
{
	if (htb_hysteresis)
		return cl->cmode == HTB_CAN_SEND ? -cl->buffer : 0;
	else
		return 0;
}