#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rx_pkt_attrib {int physt; int drvinfo_sz; int shift_sz; int crc_err; int icv_err; int qos; int bdecrypted; int mfrag; int frag_num; int mcs_rate; int rxht; int sgi; scalar_t__ pkt_len; } ;
struct TYPE_3__ {struct rx_pkt_attrib attrib; } ;
struct TYPE_4__ {TYPE_1__ hdr; } ;
union recv_frame {TYPE_2__ u; } ;
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct recv_stat {int /*<<< orphan*/  rxdw3; int /*<<< orphan*/  rxdw2; int /*<<< orphan*/  rxdw1; int /*<<< orphan*/  rxdw0; } ;

/* Variables and functions */
 int BIT (int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

void rtl8192c_query_rx_desc_status(union recv_frame *precvframe, struct recv_stat *pdesc)
{
	struct rx_pkt_attrib	*pattrib = &precvframe->u.hdr.attrib;

	//Offset 0
	pattrib->physt = (u8)((le32_to_cpu(pdesc->rxdw0) >> 26) & 0x1);
	pattrib->pkt_len =  (u16)(le32_to_cpu(pdesc->rxdw0)&0x00003fff);
	pattrib->drvinfo_sz = (u8)((le32_to_cpu(pdesc->rxdw0) >> 16) & 0xf) * 8;//uint 2^3 = 8 bytes

	pattrib->shift_sz = (u8)((le32_to_cpu(pdesc->rxdw0) >> 24) & 0x3);

	pattrib->crc_err = (u8)((le32_to_cpu(pdesc->rxdw0) >> 14) & 0x1);
	pattrib->icv_err = (u8)((le32_to_cpu(pdesc->rxdw0) >> 15) & 0x1);
	pattrib->qos = (u8)(( le32_to_cpu( pdesc->rxdw0 ) >> 23) & 0x1);// Qos data, wireless lan header length is 26
	pattrib->bdecrypted = (le32_to_cpu(pdesc->rxdw0) & BIT(27))? 0:1;

	//Offset 4
	pattrib->mfrag = (u8)((le32_to_cpu(pdesc->rxdw1) >> 27) & 0x1);//more fragment bit

	//Offset 8
	pattrib->frag_num = (u8)((le32_to_cpu(pdesc->rxdw2) >> 12) & 0xf);//fragmentation number

	//Offset 12
#ifdef CONFIG_TCP_CSUM_OFFLOAD_RX
	if ( le32_to_cpu(pdesc->rxdw3) & BIT(13)){
		pattrib->tcpchk_valid = 1; // valid
		if ( le32_to_cpu(pdesc->rxdw3) & BIT(11) ) {
			pattrib->tcp_chkrpt = 1; // correct
			//DBG_8192C("tcp csum ok\n");
		}
		else
			pattrib->tcp_chkrpt = 0; // incorrect

		if ( le32_to_cpu(pdesc->rxdw3) & BIT(12) )
			pattrib->ip_chkrpt = 1; // correct
		else
			pattrib->ip_chkrpt = 0; // incorrect
	}
	else {
		pattrib->tcpchk_valid = 0; // invalid
	}
#endif

	pattrib->mcs_rate=(u8)((le32_to_cpu(pdesc->rxdw3))&0x3f);
	pattrib->rxht=(u8)((le32_to_cpu(pdesc->rxdw3) >>6)&0x1);
	pattrib->sgi=(u8)((le32_to_cpu(pdesc->rxdw3) >>8)&0x1);
	//Offset 16
	//Offset 20

}