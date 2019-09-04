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
typedef  scalar_t__ u8 ;
struct usbnet {int /*<<< orphan*/  net; } ;

/* Variables and functions */
 int MAC_ADDR_LEN ; 
 int /*<<< orphan*/  ifup ; 
 char* macaddr ; 
 int /*<<< orphan*/  netif_dbg (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int smsc95xx_is_macaddr_param(struct usbnet *dev, u8 *dev_mac)
{
       int i, j, got_num, num;
       u8 mtbl[MAC_ADDR_LEN];

       if (macaddr[0] == ':')
               return 0;

       i = 0;
       j = 0;
       num = 0;
       got_num = 0;
       while (j < MAC_ADDR_LEN) {
               if (macaddr[i] && macaddr[i] != ':') {
                       got_num++;
                       if ('0' <= macaddr[i] && macaddr[i] <= '9')
                               num = num * 16 + macaddr[i] - '0';
                       else if ('A' <= macaddr[i] && macaddr[i] <= 'F')
                               num = num * 16 + 10 + macaddr[i] - 'A';
                       else if ('a' <= macaddr[i] && macaddr[i] <= 'f')
                               num = num * 16 + 10 + macaddr[i] - 'a';
                       else
                               break;
                       i++;
               } else if (got_num == 2) {
                       mtbl[j++] = (u8) num;
                       num = 0;
                       got_num = 0;
                       i++;
               } else {
                       break;
               }
       }

       if (j == MAC_ADDR_LEN) {
               netif_dbg(dev, ifup, dev->net, "Overriding MAC address with: "
               "%02x:%02x:%02x:%02x:%02x:%02x\n", mtbl[0], mtbl[1], mtbl[2],
                                               mtbl[3], mtbl[4], mtbl[5]);
               for (i = 0; i < MAC_ADDR_LEN; i++)
                       dev_mac[i] = mtbl[i];
               return 1;
       } else {
               return 0;
       }
}