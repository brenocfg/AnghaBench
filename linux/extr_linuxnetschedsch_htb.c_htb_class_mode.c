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
struct htb_class {scalar_t__ ctokens; scalar_t__ tokens; } ;
typedef  scalar_t__ s64 ;
typedef  enum htb_cmode { ____Placeholder_htb_cmode } htb_cmode ;

/* Variables and functions */
 int HTB_CANT_SEND ; 
 int HTB_CAN_SEND ; 
 int HTB_MAY_BORROW ; 
 scalar_t__ htb_hiwater (struct htb_class*) ; 
 scalar_t__ htb_lowater (struct htb_class*) ; 

__attribute__((used)) static inline enum htb_cmode
htb_class_mode(struct htb_class *cl, s64 *diff)
{
	s64 toks;

	if ((toks = (cl->ctokens + *diff)) < htb_lowater(cl)) {
		*diff = -toks;
		return HTB_CANT_SEND;
	}

	if ((toks = (cl->tokens + *diff)) >= htb_hiwater(cl))
		return HTB_CAN_SEND;

	*diff = -toks;
	return HTB_MAY_BORROW;
}