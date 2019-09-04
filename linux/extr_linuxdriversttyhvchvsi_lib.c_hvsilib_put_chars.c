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
struct hvsi_priv {int dummy; } ;
struct hvsi_header {int dummy; } ;
struct TYPE_2__ {int len; int /*<<< orphan*/  type; } ;
struct hvsi_data {TYPE_1__ hdr; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  HVSI_MAX_OUTGOING_DATA ; 
 int /*<<< orphan*/  VS_DATA_PACKET_HEADER ; 
 scalar_t__ WARN_ON (int) ; 
 int hvsi_send_packet (struct hvsi_priv*,TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int min (int,int /*<<< orphan*/ ) ; 

int hvsilib_put_chars(struct hvsi_priv *pv, const char *buf, int count)
{
	struct hvsi_data dp;
	int rc, adjcount = min(count, HVSI_MAX_OUTGOING_DATA);

	if (WARN_ON(!pv))
		return -ENODEV;

	dp.hdr.type = VS_DATA_PACKET_HEADER;
	dp.hdr.len = adjcount + sizeof(struct hvsi_header);
	memcpy(dp.data, buf, adjcount);
	rc = hvsi_send_packet(pv, &dp.hdr);
	if (rc <= 0)
		return rc;
	return adjcount;
}