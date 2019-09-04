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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct oid_par_priv {scalar_t__ type_of_oid; int information_buf_len; int* bytes_rw; scalar_t__ information_buf; int /*<<< orphan*/  adapter_context; } ;
struct bb_reg_param {int /*<<< orphan*/  value; scalar_t__ offset; } ;
typedef  int /*<<< orphan*/  PADAPTER ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;

/* Variables and functions */
 int BB_REG_BASE_ADDR ; 
 int /*<<< orphan*/  LOWER ; 
 int /*<<< orphan*/  NDIS_STATUS_INVALID_LENGTH ; 
 int /*<<< orphan*/  NDIS_STATUS_NOT_ACCEPTED ; 
 int /*<<< orphan*/  NDIS_STATUS_SUCCESS ; 
 scalar_t__ QUERY_OID ; 
 int /*<<< orphan*/  RAISE ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _drv_notice_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _irqlevel_changed_ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _module_mp_ ; 
 int /*<<< orphan*/  oldirql ; 
 int /*<<< orphan*/  read_bbreg (int /*<<< orphan*/ ,int,int) ; 

NDIS_STATUS oid_rt_pro_read_bb_reg_hdl(struct oid_par_priv *poid_par_priv)
{
#ifdef PLATFORM_OS_XP
	_irqL oldirql;
#endif
	struct bb_reg_param *pbbreg;
	u16 offset;
	u32 value;
	NDIS_STATUS status = NDIS_STATUS_SUCCESS;
	PADAPTER Adapter = (PADAPTER)(poid_par_priv->adapter_context);

_func_enter_;

	RT_TRACE(_module_mp_, _drv_notice_, ("+oid_rt_pro_read_bb_reg_hdl\n"));

	if (poid_par_priv->type_of_oid != QUERY_OID)
		return NDIS_STATUS_NOT_ACCEPTED;

	if (poid_par_priv->information_buf_len < sizeof(struct bb_reg_param))
		return NDIS_STATUS_INVALID_LENGTH;

	pbbreg = (struct bb_reg_param *)(poid_par_priv->information_buf);

	offset = (u16)(pbbreg->offset) & 0xFFF; //0ffset :0x800~0xfff
	if (offset < BB_REG_BASE_ADDR) offset |= BB_REG_BASE_ADDR;

	_irqlevel_changed_(&oldirql, LOWER);
	value = read_bbreg(Adapter, offset, 0xFFFFFFFF);
	_irqlevel_changed_(&oldirql, RAISE);

	pbbreg->value = value;
	*poid_par_priv->bytes_rw = poid_par_priv->information_buf_len;

	RT_TRACE(_module_mp_, _drv_notice_,
		 ("-oid_rt_pro_read_bb_reg_hdl: offset=0x%03X value:0x%08X\n",
		  offset, value));
_func_exit_;

	return status;
}