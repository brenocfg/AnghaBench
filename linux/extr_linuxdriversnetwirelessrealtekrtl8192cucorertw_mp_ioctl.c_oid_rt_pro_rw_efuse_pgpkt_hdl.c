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
struct oid_par_priv {int* bytes_rw; int information_buf_len; scalar_t__ type_of_oid; scalar_t__ information_buf; int /*<<< orphan*/  adapter_context; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  word_en; int /*<<< orphan*/  offset; } ;
typedef  TYPE_1__* PPGPKT_STRUCT ;
typedef  int /*<<< orphan*/  PGPKT_STRUCT ;
typedef  int /*<<< orphan*/  PADAPTER ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;

/* Variables and functions */
 scalar_t__ Efuse_PgPacketRead (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ Efuse_PgPacketWrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  Efuse_PowerSwitch (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LOWER ; 
 int /*<<< orphan*/  NDIS_STATUS_FAILURE ; 
 int /*<<< orphan*/  NDIS_STATUS_INVALID_LENGTH ; 
 int /*<<< orphan*/  NDIS_STATUS_SUCCESS ; 
 scalar_t__ QUERY_OID ; 
 int /*<<< orphan*/  RAISE ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ _FALSE ; 
 scalar_t__ _TRUE ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _drv_notice_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _irqlevel_changed_ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _module_mp_ ; 
 int /*<<< orphan*/  oldirql ; 

NDIS_STATUS oid_rt_pro_rw_efuse_pgpkt_hdl(struct oid_par_priv *poid_par_priv)
{
#ifdef PLATFORM_OS_XP
	_irqL		oldirql;
#endif
	PPGPKT_STRUCT	ppgpkt;
	NDIS_STATUS	status = NDIS_STATUS_SUCCESS;
	PADAPTER	Adapter = (PADAPTER)(poid_par_priv->adapter_context);

_func_enter_;

//	RT_TRACE(_module_mp_, _drv_info_, ("+oid_rt_pro_rw_efuse_pgpkt_hdl\n"));

	*poid_par_priv->bytes_rw = 0;

	if (poid_par_priv->information_buf_len < sizeof(PGPKT_STRUCT))
		return NDIS_STATUS_INVALID_LENGTH;

	ppgpkt = (PPGPKT_STRUCT)poid_par_priv->information_buf;

	_irqlevel_changed_(&oldirql, LOWER);

	if (poid_par_priv->type_of_oid == QUERY_OID)
	{
		RT_TRACE(_module_mp_, _drv_notice_,
			("oid_rt_pro_rw_efuse_pgpkt_hdl: Read offset=0x%x\n",\
			ppgpkt->offset));

		Efuse_PowerSwitch(Adapter, _FALSE, _TRUE);
		if (Efuse_PgPacketRead(Adapter, ppgpkt->offset, ppgpkt->data, _FALSE) == _TRUE)
			*poid_par_priv->bytes_rw = poid_par_priv->information_buf_len;
		else
			status = NDIS_STATUS_FAILURE;
		Efuse_PowerSwitch(Adapter, _FALSE, _FALSE);
	} else {
		RT_TRACE(_module_mp_, _drv_notice_,
			("oid_rt_pro_rw_efuse_pgpkt_hdl: Write offset=0x%x word_en=0x%x\n",\
			ppgpkt->offset, ppgpkt->word_en));

		Efuse_PowerSwitch(Adapter, _TRUE, _TRUE);
		if (Efuse_PgPacketWrite(Adapter, ppgpkt->offset, ppgpkt->word_en, ppgpkt->data, _FALSE) == _TRUE)
			*poid_par_priv->bytes_rw = poid_par_priv->information_buf_len;
		else
			status = NDIS_STATUS_FAILURE;
		Efuse_PowerSwitch(Adapter, _TRUE, _FALSE);
	}

	_irqlevel_changed_(&oldirql, RAISE);

	RT_TRACE(_module_mp_, _drv_info_,
		 ("-oid_rt_pro_rw_efuse_pgpkt_hdl: status=0x%08X\n", status));

_func_exit_;

	return status;
}