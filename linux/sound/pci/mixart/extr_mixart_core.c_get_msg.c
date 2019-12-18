#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_3__ {void* desc; void* object_id; } ;
struct mixart_msg {scalar_t__ size; scalar_t__ data; TYPE_1__ uid; void* message_id; } ;
struct mixart_mgr {int /*<<< orphan*/  msg_lock; TYPE_2__* pci; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MIXART_MEM (struct mixart_mgr*,scalar_t__) ; 
 scalar_t__ MSG_BOUND_STACK_SIZE ; 
 scalar_t__ MSG_DESCRIPTOR_SIZE ; 
 scalar_t__ MSG_HEADER_SIZE ; 
 scalar_t__ MSG_OUTBOUND_FREE_HEAD ; 
 scalar_t__ MSG_OUTBOUND_FREE_STACK ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy_fromio (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 void* readl_be (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_be (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_msg(struct mixart_mgr *mgr, struct mixart_msg *resp,
		   u32 msg_frame_address )
{
	u32  headptr;
	u32  size;
	int  err;
#ifndef __BIG_ENDIAN
	unsigned int i;
#endif

	mutex_lock(&mgr->msg_lock);
	err = 0;

	/* copy message descriptor from miXart to driver */
	size                =  readl_be(MIXART_MEM(mgr, msg_frame_address));       /* size of descriptor + response */
	resp->message_id    =  readl_be(MIXART_MEM(mgr, msg_frame_address + 4));   /* dwMessageID */
	resp->uid.object_id =  readl_be(MIXART_MEM(mgr, msg_frame_address + 8));   /* uidDest */
	resp->uid.desc      =  readl_be(MIXART_MEM(mgr, msg_frame_address + 12));  /* */

	if( (size < MSG_DESCRIPTOR_SIZE) || (resp->size < (size - MSG_DESCRIPTOR_SIZE))) {
		err = -EINVAL;
		dev_err(&mgr->pci->dev,
			"problem with response size = %d\n", size);
		goto _clean_exit;
	}
	size -= MSG_DESCRIPTOR_SIZE;

	memcpy_fromio(resp->data, MIXART_MEM(mgr, msg_frame_address + MSG_HEADER_SIZE ), size);
	resp->size = size;

	/* swap if necessary */
#ifndef __BIG_ENDIAN
	size /= 4; /* u32 size */
	for(i=0; i < size; i++) {
		((u32*)resp->data)[i] = be32_to_cpu(((__be32*)resp->data)[i]);
	}
#endif

	/*
	 * free message frame address
	 */
	headptr = readl_be(MIXART_MEM(mgr, MSG_OUTBOUND_FREE_HEAD));

	if( (headptr < MSG_OUTBOUND_FREE_STACK) || ( headptr >= (MSG_OUTBOUND_FREE_STACK+MSG_BOUND_STACK_SIZE))) {
		err = -EINVAL;
		goto _clean_exit;
	}

	/* give address back to outbound fifo */
	writel_be(msg_frame_address, MIXART_MEM(mgr, headptr));

	/* increment the outbound free head */
	headptr += 4;
	if( headptr >= (MSG_OUTBOUND_FREE_STACK+MSG_BOUND_STACK_SIZE) )
		headptr = MSG_OUTBOUND_FREE_STACK;

	writel_be(headptr, MIXART_MEM(mgr, MSG_OUTBOUND_FREE_HEAD));

 _clean_exit:
	mutex_unlock(&mgr->msg_lock);

	return err;
}