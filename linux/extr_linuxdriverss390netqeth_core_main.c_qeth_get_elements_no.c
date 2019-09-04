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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct qeth_card {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_DBF_MESSAGE (int,char*,int,int /*<<< orphan*/ ) ; 
 int QETH_MAX_BUFFER_ELEMENTS (struct qeth_card*) ; 
 int qeth_count_elements (struct sk_buff*,int) ; 

int qeth_get_elements_no(struct qeth_card *card,
		     struct sk_buff *skb, int extra_elems, int data_offset)
{
	int elements = qeth_count_elements(skb, data_offset);

	if ((elements + extra_elems) > QETH_MAX_BUFFER_ELEMENTS(card)) {
		QETH_DBF_MESSAGE(2, "Invalid size of IP packet "
			"(Number=%d / Length=%d). Discarded.\n",
			elements + extra_elems, skb->len);
		return 0;
	}
	return elements;
}