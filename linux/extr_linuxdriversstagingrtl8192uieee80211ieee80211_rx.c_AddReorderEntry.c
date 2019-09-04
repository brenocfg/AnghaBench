#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct list_head {struct list_head* next; struct list_head* prev; } ;
struct rx_ts_record {struct list_head rx_pending_pkt_list; } ;
struct TYPE_3__ {struct list_head List; int /*<<< orphan*/  SeqNum; } ;
typedef  TYPE_1__* PRX_REORDER_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  List ; 
 int /*<<< orphan*/  RX_REORDER_ENTRY ; 
 scalar_t__ SN_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SN_LESS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ list_entry (struct list_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool AddReorderEntry(struct rx_ts_record *pTS, PRX_REORDER_ENTRY pReorderEntry)
{
	struct list_head *pList = &pTS->rx_pending_pkt_list;
	while(pList->next != &pTS->rx_pending_pkt_list)
	{
		if( SN_LESS(pReorderEntry->SeqNum, ((PRX_REORDER_ENTRY)list_entry(pList->next,RX_REORDER_ENTRY,List))->SeqNum) )
		{
			pList = pList->next;
		}
		else if( SN_EQUAL(pReorderEntry->SeqNum, ((PRX_REORDER_ENTRY)list_entry(pList->next,RX_REORDER_ENTRY,List))->SeqNum) )
		{
			return false;
		}
		else
		{
			break;
		}
	}
	pReorderEntry->List.next = pList->next;
	pReorderEntry->List.next->prev = &pReorderEntry->List;
	pReorderEntry->List.prev = pList;
	pList->next = &pReorderEntry->List;

	return true;
}