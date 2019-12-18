#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* data; struct TYPE_6__* buf_end; scalar_t__ own_data; } ;
typedef  TYPE_1__ MBuf ;

/* Variables and functions */
 int /*<<< orphan*/  px_free (TYPE_1__*) ; 
 int /*<<< orphan*/  px_memset (TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*) ; 

int
mbuf_free(MBuf *mbuf)
{
	if (mbuf->own_data)
	{
		px_memset(mbuf->data, 0, mbuf->buf_end - mbuf->data);
		px_free(mbuf->data);
	}
	px_free(mbuf);
	return 0;
}