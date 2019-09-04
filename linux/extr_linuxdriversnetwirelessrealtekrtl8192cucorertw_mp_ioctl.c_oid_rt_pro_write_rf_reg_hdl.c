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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct rf_reg_param {scalar_t__ path; int offset; int value; } ;
struct oid_par_priv {scalar_t__ type_of_oid; int information_buf_len; scalar_t__ information_buf; int /*<<< orphan*/  adapter_context; } ;
typedef  int /*<<< orphan*/  PADAPTER ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  LOWER ; 
 scalar_t__ MAX_RF_PATH_NUMS ; 
 int /*<<< orphan*/  NDIS_STATUS_INVALID_LENGTH ; 
 int /*<<< orphan*/  NDIS_STATUS_NOT_ACCEPTED ; 
 int /*<<< orphan*/  NDIS_STATUS_SUCCESS ; 
 int /*<<< orphan*/  RAISE ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ SET_OID ; 
 int /*<<< orphan*/  _drv_notice_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _irqlevel_changed_ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _module_mp_ ; 
 int /*<<< orphan*/  oldirql ; 
 int /*<<< orphan*/  write_rfreg (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 

NDIS_STATUS oid_rt_pro_write_rf_reg_hdl(struct oid_par_priv *poid_par_priv)
{
#ifdef PLATFORM_OS_XP
	_irqL oldirql;
#endif
	struct rf_reg_param *pbbreg;
	u8 path;
	u8 offset;
	u32 value;
	NDIS_STATUS status = NDIS_STATUS_SUCCESS;
	PADAPTER Adapter = (PADAPTER)(poid_par_priv->adapter_context);

_func_enter_;

	RT_TRACE(_module_mp_, _drv_notice_, ("+oid_rt_pro_write_rf_reg_hdl\n"));

	if (poid_par_priv->type_of_oid != SET_OID)
		return NDIS_STATUS_NOT_ACCEPTED;

	if (poid_par_priv->information_buf_len < sizeof(struct rf_reg_param))
		return NDIS_STATUS_INVALID_LENGTH;

	pbbreg = (struct rf_reg_param *)(poid_par_priv->information_buf);

	if (pbbreg->path >= MAX_RF_PATH_NUMS)
		return NDIS_STATUS_NOT_ACCEPTED;
	if (pbbreg->offset > 0xFF)
		return NDIS_STATUS_NOT_ACCEPTED;
	if (pbbreg->value > 0xFFFFF)
		return NDIS_STATUS_NOT_ACCEPTED;

	path = (u8)pbbreg->path;
	offset = (u8)pbbreg->offset;
	value = pbbreg->value;

	RT_TRACE(_module_mp_, _drv_notice_,
		 ("oid_rt_pro_write_rf_reg_hdl: path=%d offset=0x%02X value=0x%05X\n",
		  path, offset, value));

	_irqlevel_changed_(&oldirql, LOWER);
 	write_rfreg(Adapter, path, offset, value);
	_irqlevel_changed_(&oldirql, RAISE);

_func_exit_;

	return status;
}