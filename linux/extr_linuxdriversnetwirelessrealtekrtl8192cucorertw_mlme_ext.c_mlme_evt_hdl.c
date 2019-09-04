#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint ;
typedef  size_t u8 ;
typedef  scalar_t__ u16 ;
struct evt_priv {int /*<<< orphan*/  evt_done_cnt; int /*<<< orphan*/  event_seq; } ;
struct TYPE_5__ {struct evt_priv evtpriv; } ;
typedef  TYPE_1__ _adapter ;
struct TYPE_6__ {scalar_t__ parmsize; void (* event_callback ) (TYPE_1__*,size_t*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_INC (int /*<<< orphan*/ *) ; 
 size_t H2C_SUCCESS ; 
 size_t MAX_C2HEVT ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_rtl871x_cmd_c_ ; 
 TYPE_3__* wlanevents ; 

u8 mlme_evt_hdl(_adapter *padapter, unsigned char *pbuf)
{
	u8 evt_code, evt_seq;
	u16 evt_sz;
	uint 	*peventbuf;
	void (*event_callback)(_adapter *dev, u8 *pbuf);
	struct evt_priv *pevt_priv = &(padapter->evtpriv);

	peventbuf = (uint*)pbuf;
	evt_sz = (u16)(*peventbuf&0xffff);
	evt_seq = (u8)((*peventbuf>>24)&0x7f);
	evt_code = (u8)((*peventbuf>>16)&0xff);
	
		
	#ifdef CHECK_EVENT_SEQ
	// checking event sequence...		
	if (evt_seq != (ATOMIC_READ(&pevt_priv->event_seq) & 0x7f) )
	{
		RT_TRACE(_module_rtl871x_cmd_c_,_drv_info_,("Evetn Seq Error! %d vs %d\n", (evt_seq & 0x7f), (ATOMIC_READ(&pevt_priv->event_seq) & 0x7f)));
	
		pevt_priv->event_seq = (evt_seq+1)&0x7f;

		goto _abort_event_;
	}
	#endif

	// checking if event code is valid
	if (evt_code >= MAX_C2HEVT)
	{
		RT_TRACE(_module_rtl871x_cmd_c_,_drv_err_,("\nEvent Code(%d) mismatch!\n", evt_code));
		goto _abort_event_;
	}

	// checking if event size match the event parm size	
	if ((wlanevents[evt_code].parmsize != 0) && 
			(wlanevents[evt_code].parmsize != evt_sz))
	{
			
		RT_TRACE(_module_rtl871x_cmd_c_,_drv_err_,("\nEvent(%d) Parm Size mismatch (%d vs %d)!\n", 
			evt_code, wlanevents[evt_code].parmsize, evt_sz));
		goto _abort_event_;	
			
	}

	ATOMIC_INC(&pevt_priv->event_seq);

	peventbuf += 2;
				
	if(peventbuf)
	{
		event_callback = wlanevents[evt_code].event_callback;
		event_callback(padapter, (u8*)peventbuf);

		pevt_priv->evt_done_cnt++;
	}


_abort_event_:


	return H2C_SUCCESS;
		
}