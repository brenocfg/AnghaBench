#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* osdmap; } ;
struct TYPE_6__ {TYPE_1__* monmap; } ;
struct ceph_client {TYPE_4__ osdc; TYPE_2__ monc; } ;
struct TYPE_7__ {scalar_t__ epoch; } ;
struct TYPE_5__ {scalar_t__ epoch; } ;

/* Variables and functions */

__attribute__((used)) static bool have_mon_and_osd_map(struct ceph_client *client)
{
	return client->monc.monmap && client->monc.monmap->epoch &&
	       client->osdc.osdmap && client->osdc.osdmap->epoch;
}