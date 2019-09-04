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
struct dvobj_priv {scalar_t__ ishighspeed; } ;
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 int TXDESC_SIZE ; 
 struct dvobj_priv* adapter_to_dvobj (int /*<<< orphan*/ *) ; 

int urb_zero_packet_chk(_adapter *padapter, int sz)
{
	int blnSetTxDescOffset;
	struct dvobj_priv	*pdvobj = adapter_to_dvobj(padapter);	

	if ( pdvobj->ishighspeed )
	{
		if ( ( (sz + TXDESC_SIZE) % 512 ) == 0 ) {
			blnSetTxDescOffset = 1;
		} else {
			blnSetTxDescOffset = 0;
		}
	}
	else
	{
		if ( ( (sz + TXDESC_SIZE) % 64 ) == 0 ) 	{
			blnSetTxDescOffset = 1;
		} else {
			blnSetTxDescOffset = 0;
		}
	}
	
	return blnSetTxDescOffset;
	
}