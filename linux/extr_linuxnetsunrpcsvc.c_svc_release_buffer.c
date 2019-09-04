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
struct svc_rqst {scalar_t__* rq_pages; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  put_page (scalar_t__) ; 

__attribute__((used)) static void
svc_release_buffer(struct svc_rqst *rqstp)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(rqstp->rq_pages); i++)
		if (rqstp->rq_pages[i])
			put_page(rqstp->rq_pages[i]);
}