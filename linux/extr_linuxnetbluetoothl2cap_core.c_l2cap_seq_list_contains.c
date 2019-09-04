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
typedef  size_t u16 ;
struct l2cap_seq_list {scalar_t__* list; size_t mask; } ;

/* Variables and functions */
 scalar_t__ L2CAP_SEQ_LIST_CLEAR ; 

__attribute__((used)) static inline bool l2cap_seq_list_contains(struct l2cap_seq_list *seq_list,
					   u16 seq)
{
	/* Constant-time check for list membership */
	return seq_list->list[seq & seq_list->mask] != L2CAP_SEQ_LIST_CLEAR;
}