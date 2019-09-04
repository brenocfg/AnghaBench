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
struct smc_llc_send_work {int llclen; int /*<<< orphan*/  work; int /*<<< orphan*/  llcbuf; struct smc_link* link; } ;
struct smc_link {int /*<<< orphan*/  llc_wq; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct smc_llc_send_work* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smc_llc_send_message_work ; 

__attribute__((used)) static int smc_llc_send_message(struct smc_link *link, void *llcbuf, int llclen)
{
	struct smc_llc_send_work *wrk = kmalloc(sizeof(*wrk), GFP_ATOMIC);

	if (!wrk)
		return -ENOMEM;
	INIT_WORK(&wrk->work, smc_llc_send_message_work);
	wrk->link = link;
	wrk->llclen = llclen;
	memcpy(&wrk->llcbuf, llcbuf, llclen);
	queue_work(link->llc_wq, &wrk->work);
	return 0;
}