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
typedef  int /*<<< orphan*/  u8 ;
struct sprd_mcdt_chan {int dummy; } ;
typedef  enum sprd_mcdt_channel_type { ____Placeholder_sprd_mcdt_channel_type } sprd_mcdt_channel_type ;

/* Variables and functions */

struct sprd_mcdt_chan *sprd_mcdt_request_chan(u8 channel,
					      enum sprd_mcdt_channel_type type)
{
	return NULL;
}