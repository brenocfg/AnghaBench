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
struct iw_point {int flags; int /*<<< orphan*/  pointer; scalar_t__ length; } ;
union iwreq_data {struct iw_point data; } ;
typedef  scalar_t__ uint ;
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct oid_par_priv {int dummy; } ;
struct net_device {int dummy; } ;
struct mp_ioctl_param {scalar_t__ subcode; int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct mp_ioctl_handler {int dummy; } ;
struct iw_request_info {int dummy; } ;
typedef  int /*<<< orphan*/  PADAPTER ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ MAX_MP_IOCTL_SUBCODE ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_rtl871x_ioctl_os_c ; 
 scalar_t__ copy_from_user (int*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,int*,scalar_t__) ; 
 int /*<<< orphan*/  rtw_dbg_mode_hdl (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rtw_malloc (scalar_t__) ; 
 int /*<<< orphan*/  rtw_mfree (int*,scalar_t__) ; 
 int /*<<< orphan*/  rtw_netdev_priv (struct net_device*) ; 

__attribute__((used)) static int rtw_mp_ioctl_hdl(struct net_device *dev, struct iw_request_info *info,
						union iwreq_data *wrqu, char *extra)
{
	int ret = 0;
	u32 BytesRead, BytesWritten, BytesNeeded;
	struct oid_par_priv	oid_par;
	struct mp_ioctl_handler	*phandler;
	struct mp_ioctl_param	*poidparam;
	uint status=0;
	u16 len;
	u8 *pparmbuf = NULL, bset;
	PADAPTER padapter = (PADAPTER)rtw_netdev_priv(dev);
	struct iw_point *p = &wrqu->data;

	//DBG_871X("+rtw_mp_ioctl_hdl\n");

	//mutex_lock(&ioctl_mutex);

	if ((!p->length) || (!p->pointer)) {
		ret = -EINVAL;
		goto _rtw_mp_ioctl_hdl_exit;
	}

	pparmbuf = NULL;
	bset = (u8)(p->flags & 0xFFFF);
	len = p->length;
	pparmbuf = (u8*)rtw_malloc(len);
	if (pparmbuf == NULL){
		ret = -ENOMEM;
		goto _rtw_mp_ioctl_hdl_exit;
	}

	if (copy_from_user(pparmbuf, p->pointer, len)) {
		ret = -EFAULT;
		goto _rtw_mp_ioctl_hdl_exit;
	}

	poidparam = (struct mp_ioctl_param *)pparmbuf;
	RT_TRACE(_module_rtl871x_ioctl_os_c, _drv_info_,
		 ("rtw_mp_ioctl_hdl: subcode [%d], len[%d], buffer_len[%d]\r\n",
		  poidparam->subcode, poidparam->len, len));

	if (poidparam->subcode >= MAX_MP_IOCTL_SUBCODE) {
		RT_TRACE(_module_rtl871x_ioctl_os_c, _drv_err_, ("no matching drvext subcodes\r\n"));
		ret = -EINVAL;
		goto _rtw_mp_ioctl_hdl_exit;
	}

	//DBG_871X("%s: %d\n", __func__, poidparam->subcode);

#ifdef CONFIG_MP_INCLUDED 
	phandler = mp_ioctl_hdl + poidparam->subcode;

	if ((phandler->paramsize != 0) && (poidparam->len < phandler->paramsize))
	{
		RT_TRACE(_module_rtl871x_ioctl_os_c, _drv_err_,
			 ("no matching drvext param size %d vs %d\r\n",
			  poidparam->len, phandler->paramsize));
		ret = -EINVAL;
		goto _rtw_mp_ioctl_hdl_exit;
	}

	if (phandler->handler)
	{
		oid_par.adapter_context = padapter;
		oid_par.oid = phandler->oid;
		oid_par.information_buf = poidparam->data;
		oid_par.information_buf_len = poidparam->len;
		oid_par.dbg = 0;

		BytesWritten = 0;
		BytesNeeded = 0;

		if (bset) {
			oid_par.bytes_rw = &BytesRead;
			oid_par.bytes_needed = &BytesNeeded;
			oid_par.type_of_oid = SET_OID;
		} else {
			oid_par.bytes_rw = &BytesWritten;
			oid_par.bytes_needed = &BytesNeeded;
			oid_par.type_of_oid = QUERY_OID;
		}

		status = phandler->handler(&oid_par);

		//todo:check status, BytesNeeded, etc.
	}
	else {
		DBG_871X("rtw_mp_ioctl_hdl(): err!, subcode=%d, oid=%d, handler=%p\n", 
			poidparam->subcode, phandler->oid, phandler->handler);
		ret = -EFAULT;
		goto _rtw_mp_ioctl_hdl_exit;
	}
#else

	rtw_dbg_mode_hdl(padapter, poidparam->subcode, poidparam->data, poidparam->len);
	
#endif

	if (bset == 0x00) {//query info
		if (copy_to_user(p->pointer, pparmbuf, len))
			ret = -EFAULT;
	}

	if (status) {
		ret = -EFAULT;
		goto _rtw_mp_ioctl_hdl_exit;
	}

_rtw_mp_ioctl_hdl_exit:

	if (pparmbuf)
		rtw_mfree(pparmbuf, len);

	//mutex_unlock(&ioctl_mutex);

	return ret;
}