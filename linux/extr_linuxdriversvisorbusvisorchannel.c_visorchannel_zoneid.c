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
struct TYPE_2__ {int /*<<< orphan*/  zone_guid; } ;
struct visorchannel {TYPE_1__ chan_hdr; } ;

/* Variables and functions */
 char* visorchannel_guid_id (int /*<<< orphan*/ *,char*) ; 

char *visorchannel_zoneid(struct visorchannel *channel, char *s)
{
	return visorchannel_guid_id(&channel->chan_hdr.zone_guid, s);
}