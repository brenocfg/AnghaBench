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
typedef  void* u8 ;
struct list_head {int dummy; } ;
struct dccp_ackvec_parsed {void** vec; int /*<<< orphan*/  node; void* nonce; void* len; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct dccp_ackvec_parsed* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 

int dccp_ackvec_parsed_add(struct list_head *head, u8 *vec, u8 len, u8 nonce)
{
	struct dccp_ackvec_parsed *new = kmalloc(sizeof(*new), GFP_ATOMIC);

	if (new == NULL)
		return -ENOBUFS;
	new->vec   = vec;
	new->len   = len;
	new->nonce = nonce;

	list_add_tail(&new->node, head);
	return 0;
}