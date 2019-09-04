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
struct tx_desc {int /*<<< orphan*/  txdw1; } ;
struct pkt_attrib {int encrypt; int /*<<< orphan*/  bswenc; } ;

/* Variables and functions */
#define  _AES_ 133 
#define  _NO_PRIVACY_ 132 
#define  _TKIP_ 131 
#define  _TKIP_WTMIC_ 130 
#define  _WEP104_ 129 
#define  _WEP40_ 128 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 

void fill_txdesc_sectype(struct pkt_attrib *pattrib, struct tx_desc *ptxdesc)
{
	if ((pattrib->encrypt > 0) && !pattrib->bswenc)
	{
		switch (pattrib->encrypt)
		{	
			//SEC_TYPE
			case _WEP40_:
			case _WEP104_:
					ptxdesc->txdw1 |= cpu_to_le32((0x01<<22)&0x00c00000);
					break;				
			case _TKIP_:
			case _TKIP_WTMIC_:	
					//ptxdesc->txdw1 |= cpu_to_le32((0x02<<22)&0x00c00000);
					ptxdesc->txdw1 |= cpu_to_le32((0x01<<22)&0x00c00000);
					break;
			case _AES_:
					ptxdesc->txdw1 |= cpu_to_le32((0x03<<22)&0x00c00000);
					break;
			case _NO_PRIVACY_:
			default:
					break;
		
		}
		
	}

}