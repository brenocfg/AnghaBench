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
typedef  int /*<<< orphan*/  wiz_NetTimeout ;
typedef  int /*<<< orphan*/  wiz_NetInfo ;
typedef  int /*<<< orphan*/  netmode_type ;
typedef  int int8_t ;
typedef  int ctlnetwork_type ;

/* Variables and functions */
#define  CN_GET_NETINFO 133 
#define  CN_GET_NETMODE 132 
#define  CN_GET_TIMEOUT 131 
#define  CN_SET_NETINFO 130 
#define  CN_SET_NETMODE 129 
#define  CN_SET_TIMEOUT 128 
 int /*<<< orphan*/  wizchip_getnetinfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wizchip_getnetmode () ; 
 int /*<<< orphan*/  wizchip_gettimeout (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wizchip_setnetinfo (int /*<<< orphan*/ *) ; 
 int wizchip_setnetmode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wizchip_settimeout (int /*<<< orphan*/ *) ; 

int8_t ctlnetwork(ctlnetwork_type cntype, void* arg)
{
   
   switch(cntype)
   {
      case CN_SET_NETINFO:
         wizchip_setnetinfo((wiz_NetInfo*)arg);
         break;
      case CN_GET_NETINFO:
         wizchip_getnetinfo((wiz_NetInfo*)arg);
         break;
      case CN_SET_NETMODE:
         return wizchip_setnetmode(*(netmode_type*)arg);
      case CN_GET_NETMODE:
         *(netmode_type*)arg = wizchip_getnetmode();
         break;
      case CN_SET_TIMEOUT:
         wizchip_settimeout((wiz_NetTimeout*)arg);
         break;
      case CN_GET_TIMEOUT:
         wizchip_gettimeout((wiz_NetTimeout*)arg);
         break;
      default:
         return -1;
   }
   return 0;
}