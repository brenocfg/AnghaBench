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
typedef  char WCHAR ;
typedef  int DWORD ;

/* Variables and functions */
#define  IF_TYPE_ETHERNET_CSMACD 131 
#define  IF_TYPE_IEEE1394 130 
#define  IF_TYPE_IEEE80211 129 
#define  IF_TYPE_TUNNEL 128 

__attribute__((used)) static const WCHAR *get_adaptertype( DWORD type, int *physical )
{
    static const WCHAR ethernetW[] = {'E','t','h','e','r','n','e','t',' ','8','0','2','.','3',0};
    static const WCHAR wirelessW[] = {'W','i','r','e','l','e','s','s',0};
    static const WCHAR firewireW[] = {'1','3','9','4',0};
    static const WCHAR tunnelW[]   = {'T','u','n','n','e','l',0};

    switch (type)
    {
    case IF_TYPE_ETHERNET_CSMACD: *physical = -1; return ethernetW;
    case IF_TYPE_IEEE80211:       *physical = -1; return wirelessW;
    case IF_TYPE_IEEE1394:        *physical = -1; return firewireW;
    case IF_TYPE_TUNNEL:          *physical = 0; return tunnelW;
    default:                      *physical = 0; return NULL;
    }
}