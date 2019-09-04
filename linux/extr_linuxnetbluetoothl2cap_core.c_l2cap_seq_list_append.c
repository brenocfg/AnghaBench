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
struct l2cap_seq_list {size_t mask; size_t* list; size_t tail; size_t head; } ;

/* Variables and functions */
 size_t L2CAP_SEQ_LIST_CLEAR ; 
 size_t L2CAP_SEQ_LIST_TAIL ; 

__attribute__((used)) static void l2cap_seq_list_append(struct l2cap_seq_list *seq_list, u16 seq)
{
	u16 mask = seq_list->mask;

	/* All appends happen in constant time */

	if (seq_list->list[seq & mask] != L2CAP_SEQ_LIST_CLEAR)
		return;

	if (seq_list->tail == L2CAP_SEQ_LIST_CLEAR)
		seq_list->head = seq;
	else
		seq_list->list[seq_list->tail & mask] = seq;

	seq_list->tail = seq;
	seq_list->list[seq & mask] = L2CAP_SEQ_LIST_TAIL;
}