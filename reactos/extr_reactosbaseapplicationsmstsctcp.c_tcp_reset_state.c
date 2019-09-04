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
struct TYPE_4__ {int /*<<< orphan*/ * channel_hdr; int /*<<< orphan*/ * rdp_hdr; int /*<<< orphan*/ * sec_hdr; int /*<<< orphan*/ * mcs_hdr; int /*<<< orphan*/ * iso_hdr; scalar_t__ size; int /*<<< orphan*/ * data; int /*<<< orphan*/ * end; int /*<<< orphan*/ * p; } ;
struct TYPE_3__ {int /*<<< orphan*/ * channel_hdr; int /*<<< orphan*/ * rdp_hdr; int /*<<< orphan*/ * sec_hdr; int /*<<< orphan*/ * mcs_hdr; int /*<<< orphan*/ * iso_hdr; scalar_t__ size; int /*<<< orphan*/ * data; int /*<<< orphan*/ * end; int /*<<< orphan*/ * p; } ;

/* Variables and functions */
 int STREAM_COUNT ; 
 TYPE_2__ g_in ; 
 TYPE_1__* g_out ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ *) ; 

void
tcp_reset_state(void)
{
	int i;

	/* Clear the incoming stream */
	if (g_in.data != NULL)
		xfree(g_in.data);
	g_in.p = NULL;
	g_in.end = NULL;
	g_in.data = NULL;
	g_in.size = 0;
	g_in.iso_hdr = NULL;
	g_in.mcs_hdr = NULL;
	g_in.sec_hdr = NULL;
	g_in.rdp_hdr = NULL;
	g_in.channel_hdr = NULL;

	/* Clear the outgoing stream(s) */
	for (i = 0; i < STREAM_COUNT; i++)
	{
		if (g_out[i].data != NULL)
			xfree(g_out[i].data);
		g_out[i].p = NULL;
		g_out[i].end = NULL;
		g_out[i].data = NULL;
		g_out[i].size = 0;
		g_out[i].iso_hdr = NULL;
		g_out[i].mcs_hdr = NULL;
		g_out[i].sec_hdr = NULL;
		g_out[i].rdp_hdr = NULL;
		g_out[i].channel_hdr = NULL;
	}
}