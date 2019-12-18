#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ mcs_id; } ;
typedef  int /*<<< orphan*/  STREAM ;
typedef  int /*<<< orphan*/  RD_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 scalar_t__ MCS_GLOBAL_CHANNEL ; 
 scalar_t__ MCS_USERCHANNEL_BASE ; 
 int /*<<< orphan*/  True ; 
 TYPE_1__* g_channels ; 
 scalar_t__ g_mcs_userid ; 
 unsigned int g_num_channels ; 
 int /*<<< orphan*/  iso_disconnect () ; 
 int /*<<< orphan*/  mcs_recv_aucf (scalar_t__*) ; 
 int /*<<< orphan*/  mcs_recv_cjcf () ; 
 int /*<<< orphan*/  mcs_recv_connect_response (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcs_send_aurq () ; 
 int /*<<< orphan*/  mcs_send_cjrq (scalar_t__) ; 
 int /*<<< orphan*/  mcs_send_connect_initial (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcs_send_edrq () ; 

RD_BOOL
mcs_connect_finalize(STREAM mcs_data)
{
	unsigned int i;

	mcs_send_connect_initial(mcs_data);
	if (!mcs_recv_connect_response(mcs_data))
		goto error;

	mcs_send_edrq();

	mcs_send_aurq();
	if (!mcs_recv_aucf(&g_mcs_userid))
		goto error;

	mcs_send_cjrq(g_mcs_userid + MCS_USERCHANNEL_BASE);

	if (!mcs_recv_cjcf())
		goto error;

	mcs_send_cjrq(MCS_GLOBAL_CHANNEL);
	if (!mcs_recv_cjcf())
		goto error;

	for (i = 0; i < g_num_channels; i++)
	{
		mcs_send_cjrq(g_channels[i].mcs_id);
		if (!mcs_recv_cjcf())
			goto error;
	}
	return True;

      error:
	iso_disconnect();
	return False;
}