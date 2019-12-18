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
struct hlist_node {int dummy; } ;
struct hlist_head {int dummy; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 struct hlist_node* SEQ_START_TOKEN ; 
 struct hlist_node* seq_hlist_start (struct hlist_head*,scalar_t__) ; 

struct hlist_node *seq_hlist_start_head(struct hlist_head *head, loff_t pos)
{
	if (!pos)
		return SEQ_START_TOKEN;

	return seq_hlist_start(head, pos - 1);
}