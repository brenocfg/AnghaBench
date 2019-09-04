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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct rf_reg_param {int /*<<< orphan*/  value; scalar_t__ offset; scalar_t__ path; } ;
struct oid_par_priv {scalar_t__ type_of_oid; int information_buf_len; scalar_t__ information_buf; scalar_t__ adapter_context; } ;
struct _adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ RF_PATH_B ; 
 int /*<<< orphan*/  RNDIS_STATUS_INVALID_LENGTH ; 
 int /*<<< orphan*/  RNDIS_STATUS_NOT_ACCEPTED ; 
 int /*<<< orphan*/  RNDIS_STATUS_SUCCESS ; 
 scalar_t__ SET_OID ; 
 int /*<<< orphan*/  r8712_rf_reg_write (struct _adapter*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

uint oid_rt_pro_write_rf_reg_hdl(struct oid_par_priv *poid_par_priv)
{
	struct _adapter *Adapter = (struct _adapter *)
				   (poid_par_priv->adapter_context);
	struct rf_reg_param *pbbreg;
	u8 path;
	u8 offset;
	u32 value;

	if (poid_par_priv->type_of_oid != SET_OID)
		return RNDIS_STATUS_NOT_ACCEPTED;
	if (poid_par_priv->information_buf_len < sizeof(struct rf_reg_param))
		return RNDIS_STATUS_INVALID_LENGTH;
	pbbreg = (struct rf_reg_param *)(poid_par_priv->information_buf);
	path = (u8)pbbreg->path;
	if (path > RF_PATH_B)
		return RNDIS_STATUS_NOT_ACCEPTED;
	offset = (u8)pbbreg->offset;
	value = pbbreg->value;
	r8712_rf_reg_write(Adapter, path, offset, value);
	return RNDIS_STATUS_SUCCESS;
}