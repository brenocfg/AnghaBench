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
struct hib_bio_batch {int /*<<< orphan*/  error; int /*<<< orphan*/  wait; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_OK ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hib_init_batch(struct hib_bio_batch *hb)
{
	atomic_set(&hb->count, 0);
	init_waitqueue_head(&hb->wait);
	hb->error = BLK_STS_OK;
}