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
struct wdrr_bucket {struct sk_buff* tail; struct sk_buff* head; } ;
struct sk_buff {struct sk_buff* next; } ;

/* Variables and functions */

__attribute__((used)) static void bucket_add(struct wdrr_bucket *bucket, struct sk_buff *skb)
{
	if (bucket->head == NULL)
		bucket->head = skb;
	else
		bucket->tail->next = skb;
	bucket->tail = skb;
	skb->next = NULL;
}