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
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zzz ;
struct Masscan {int nic_count; TYPE_3__* nic; } ;
struct TYPE_4__ {int first; int last; } ;
struct TYPE_5__ {TYPE_1__ ip; } ;
struct TYPE_6__ {char* ifname; int* my_mac; int router_ip; int* router_mac; scalar_t__ my_mac_count; TYPE_2__ src; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,...) ; 
 scalar_t__ memcmp (int*,char*,int) ; 
 int /*<<< orphan*/  sprintf_s (char*,int,char*,unsigned int) ; 

__attribute__((used)) static void
masscan_echo_nic(struct Masscan *masscan, FILE *fp, unsigned i)
{
    char zzz[64];

    /* If we have only one adapter, then don't print the array indexes.
     * Otherwise, we need to print the array indexes to distinguish
     * the NICs from each other */
    if (masscan->nic_count <= 1)
        zzz[0] = '\0';
    else
        sprintf_s(zzz, sizeof(zzz), "[%u]", i);

    if (masscan->nic[i].ifname[0])
        fprintf(fp, "adapter%s = %s\n", zzz, masscan->nic[i].ifname);
    
    if (masscan->nic[i].src.ip.first+1 == masscan->nic[i].src.ip.last)
        fprintf(fp, "adapter-ip%s = %u.%u.%u.%u\n", zzz,
            (masscan->nic[i].src.ip.first>>24)&0xFF,
            (masscan->nic[i].src.ip.first>>16)&0xFF,
            (masscan->nic[i].src.ip.first>> 8)&0xFF,
            (masscan->nic[i].src.ip.first>> 0)&0xFF
            );
    else if (masscan->nic[i].src.ip.first+1 < masscan->nic[i].src.ip.last)
        fprintf(fp, "adapter-ip%s = %u.%u.%u.%u-%u.%u.%u.%u\n", zzz,
            (masscan->nic[i].src.ip.first>>24)&0xFF,
            (masscan->nic[i].src.ip.first>>16)&0xFF,
            (masscan->nic[i].src.ip.first>> 8)&0xFF,
            (masscan->nic[i].src.ip.first>> 0)&0xFF,
            (masscan->nic[i].src.ip.last>>24)&0xFF,
            (masscan->nic[i].src.ip.last>>16)&0xFF,
            (masscan->nic[i].src.ip.last>> 8)&0xFF,
            (masscan->nic[i].src.ip.last>> 0)&0xFF
            );

    if (masscan->nic[i].my_mac_count)
        fprintf(fp, "adapter-mac%s = %02x:%02x:%02x:%02x:%02x:%02x\n", zzz,
                masscan->nic[i].my_mac[0],
                masscan->nic[i].my_mac[1],
                masscan->nic[i].my_mac[2],
                masscan->nic[i].my_mac[3],
                masscan->nic[i].my_mac[4],
                masscan->nic[i].my_mac[5]);
    if (masscan->nic[i].router_ip) {
        fprintf(fp, "router-ip%s = %u.%u.%u.%u\n", zzz,
            (masscan->nic[i].router_ip>>24)&0xFF,
            (masscan->nic[i].router_ip>>16)&0xFF,
            (masscan->nic[i].router_ip>> 8)&0xFF,
            (masscan->nic[i].router_ip>> 0)&0xFF
            );
    } else if (memcmp(masscan->nic[i].router_mac, "\0\0\0\0\0\0", 6) != 0)
        fprintf(fp, "router-mac%s = %02x:%02x:%02x:%02x:%02x:%02x\n", zzz,
            masscan->nic[i].router_mac[0],
            masscan->nic[i].router_mac[1],
            masscan->nic[i].router_mac[2],
            masscan->nic[i].router_mac[3],
            masscan->nic[i].router_mac[4],
            masscan->nic[i].router_mac[5]);

}