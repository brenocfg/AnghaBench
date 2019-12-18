#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ type; char* character; TYPE_1__* key; int /*<<< orphan*/  suffix; } ;
struct TYPE_4__ {scalar_t__ is_digit; } ;
typedef  TYPE_2__ FormatNode ;

/* Variables and functions */
 scalar_t__ NODE_TYPE_ACTION ; 
 scalar_t__ NODE_TYPE_END ; 
 scalar_t__ S_THth (int /*<<< orphan*/ ) ; 
 scalar_t__ isdigit (unsigned char) ; 

__attribute__((used)) static bool
is_next_separator(FormatNode *n)
{
	if (n->type == NODE_TYPE_END)
		return false;

	if (n->type == NODE_TYPE_ACTION && S_THth(n->suffix))
		return true;

	/*
	 * Next node
	 */
	n++;

	/* end of format string is treated like a non-digit separator */
	if (n->type == NODE_TYPE_END)
		return true;

	if (n->type == NODE_TYPE_ACTION)
	{
		if (n->key->is_digit)
			return false;

		return true;
	}
	else if (n->character[1] == '\0' &&
			 isdigit((unsigned char) n->character[0]))
		return false;

	return true;				/* some non-digit input (separator) */
}