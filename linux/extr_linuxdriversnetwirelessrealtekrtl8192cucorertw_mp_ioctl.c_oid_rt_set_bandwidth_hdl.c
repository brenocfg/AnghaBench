#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct oid_par_priv {scalar_t__ type_of_oid; int information_buf_len; scalar_t__ information_buf; int /*<<< orphan*/  adapter_context; } ;
struct TYPE_4__ {void* prime_channel_offset; void* bandwidth; } ;
struct TYPE_5__ {TYPE_1__ mppriv; } ;
typedef  TYPE_2__* PADAPTER ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;

/* Variables and functions */
 scalar_t__ HAL_PRIME_CHNL_OFFSET_DONT_CARE ; 
 scalar_t__ HT_CHANNEL_WIDTH_20 ; 
 scalar_t__ HT_CHANNEL_WIDTH_40 ; 
 int /*<<< orphan*/  LOWER ; 
 int /*<<< orphan*/  NDIS_STATUS_INVALID_LENGTH ; 
 int /*<<< orphan*/  NDIS_STATUS_NOT_ACCEPTED ; 
 int /*<<< orphan*/  NDIS_STATUS_SUCCESS ; 
 int /*<<< orphan*/  RAISE ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ SET_OID ; 
 int /*<<< orphan*/  SetBandwidth (TYPE_2__*) ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _drv_notice_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _irqlevel_changed_ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _module_mp_ ; 
 int /*<<< orphan*/  oldirql ; 

NDIS_STATUS oid_rt_set_bandwidth_hdl(struct oid_par_priv *poid_par_priv)
{
#ifdef PLATFORM_OS_XP
	_irqL		oldirql;
#endif
	u16		bandwidth;
	u16		channel_offset;
	NDIS_STATUS	status = NDIS_STATUS_SUCCESS;
	PADAPTER	padapter = (PADAPTER)(poid_par_priv->adapter_context);

_func_enter_;

	RT_TRACE(_module_mp_, _drv_info_,
		 ("+oid_rt_set_bandwidth_hdl\n"));

	if (poid_par_priv->type_of_oid != SET_OID)
		return NDIS_STATUS_NOT_ACCEPTED;

	if (poid_par_priv->information_buf_len < sizeof(u32))
		return NDIS_STATUS_INVALID_LENGTH;

	bandwidth = *((u32*)poid_par_priv->information_buf);//4
	channel_offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE;

	if (bandwidth != HT_CHANNEL_WIDTH_40)
		bandwidth = HT_CHANNEL_WIDTH_20;
	padapter->mppriv.bandwidth = (u8)bandwidth;
	padapter->mppriv.prime_channel_offset = (u8)channel_offset;

	_irqlevel_changed_(&oldirql, LOWER);
	SetBandwidth(padapter);
	_irqlevel_changed_(&oldirql, RAISE);

	RT_TRACE(_module_mp_, _drv_notice_,
		 ("-oid_rt_set_bandwidth_hdl: bandwidth=%d channel_offset=%d\n",
		  bandwidth, channel_offset));

_func_exit_;

	return status;
}