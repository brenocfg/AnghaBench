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
struct smb_rqst {int rq_npages; int /*<<< orphan*/ * rq_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 

void
smb3_free_compound_rqst(int num_rqst, struct smb_rqst *rqst)
{
	int i, j;

	for (i = 0; i < num_rqst; i++) {
		if (rqst[i].rq_pages) {
			for (j = rqst[i].rq_npages - 1; j >= 0; j--)
				put_page(rqst[i].rq_pages[j]);
			kfree(rqst[i].rq_pages);
		}
	}
}