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
struct raw3215_req {scalar_t__ type; struct raw3215_req* next; } ;

/* Variables and functions */
 scalar_t__ RAW3215_FREE ; 
 struct raw3215_req* raw3215_freelist ; 
 int /*<<< orphan*/  raw3215_freelist_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void raw3215_free_req(struct raw3215_req *req)
{
	unsigned long flags;

	if (req->type == RAW3215_FREE)
		return;		/* don't free a free request */
	req->type = RAW3215_FREE;
	spin_lock_irqsave(&raw3215_freelist_lock, flags);
	req->next = raw3215_freelist;
	raw3215_freelist = req;
	spin_unlock_irqrestore(&raw3215_freelist_lock, flags);
}