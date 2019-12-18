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
struct rpc_rqst {int rq_enc_pages_num; int /*<<< orphan*/ * rq_release_snd_buf; int /*<<< orphan*/ * rq_enc_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
priv_release_snd_buf(struct rpc_rqst *rqstp)
{
	int i;

	for (i=0; i < rqstp->rq_enc_pages_num; i++)
		__free_page(rqstp->rq_enc_pages[i]);
	kfree(rqstp->rq_enc_pages);
	rqstp->rq_release_snd_buf = NULL;
}