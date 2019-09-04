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

/* Variables and functions */
 int /*<<< orphan*/  MR_RST ; 
 int /*<<< orphan*/  getGAR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getMR () ; 
 int /*<<< orphan*/  getSHAR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getSIPR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getSUBR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setGAR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setMR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setSHAR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setSIPR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setSUBR (int /*<<< orphan*/ *) ; 

void wizchip_sw_reset(void)
{
   uint8_t gw[4], sn[4], sip[4];
   uint8_t mac[6];
   getSHAR(mac);
   getGAR(gw);  getSUBR(sn);  getSIPR(sip);
   setMR(MR_RST);
   getMR(); // for delay
   setSHAR(mac);
   setGAR(gw);
   setSUBR(sn);
   setSIPR(sip);
}