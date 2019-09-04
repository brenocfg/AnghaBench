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
typedef  int /*<<< orphan*/  uint ;
struct oid_par_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RNDIS_STATUS_SUCCESS ; 

uint oid_rt_scan_with_magic_packet_hdl(struct oid_par_priv
					      *poid_par_priv)
{
	return RNDIS_STATUS_SUCCESS;
}