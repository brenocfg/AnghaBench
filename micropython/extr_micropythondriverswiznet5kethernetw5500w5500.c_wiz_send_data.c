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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 int WIZCHIP_TXBUF_BLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIZCHIP_WRITE_BUF (int,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ getSn_TX_WR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setSn_TX_WR (int /*<<< orphan*/ ,scalar_t__) ; 

void wiz_send_data(uint8_t sn, uint8_t *wizdata, uint16_t len)
{
   uint16_t ptr = 0;
   uint32_t addrsel = 0;

   if(len == 0)  return;
   ptr = getSn_TX_WR(sn);
   //M20140501 : implict type casting -> explict type casting
   //addrsel = (ptr << 8) + (WIZCHIP_TXBUF_BLOCK(sn) << 3);
   addrsel = ((uint32_t)ptr << 8) + (WIZCHIP_TXBUF_BLOCK(sn) << 3);
   //
   WIZCHIP_WRITE_BUF(addrsel,wizdata, len);
   
   ptr += len;
   setSn_TX_WR(sn,ptr);
}