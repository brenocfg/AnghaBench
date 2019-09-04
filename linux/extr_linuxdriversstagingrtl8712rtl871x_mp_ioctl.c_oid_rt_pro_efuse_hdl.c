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
struct oid_par_priv {scalar_t__ type_of_oid; } ;

/* Variables and functions */
 scalar_t__ QUERY_OID ; 
 int /*<<< orphan*/  RNDIS_STATUS_SUCCESS ; 
 int /*<<< orphan*/  oid_rt_pro_read_efuse_hdl (struct oid_par_priv*) ; 
 int /*<<< orphan*/  oid_rt_pro_write_efuse_hdl (struct oid_par_priv*) ; 

uint oid_rt_pro_efuse_hdl(struct oid_par_priv *poid_par_priv)
{
	uint status = RNDIS_STATUS_SUCCESS;

	if (poid_par_priv->type_of_oid == QUERY_OID)
		status = oid_rt_pro_read_efuse_hdl(poid_par_priv);
	else
		status = oid_rt_pro_write_efuse_hdl(poid_par_priv);
	return status;
}