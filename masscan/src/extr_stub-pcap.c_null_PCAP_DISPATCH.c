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
typedef  void* PCAP_HANDLE_PACKET ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSEDPARM (void*) ; 
 int pcap_dispatch (void*,unsigned int,void*,void*) ; 

__attribute__((used)) static unsigned null_PCAP_DISPATCH(void *hPcap, unsigned how_many_packets, PCAP_HANDLE_PACKET handler, void *handle_data)
{
#ifdef STATICPCAP
    return pcap_dispatch(hPcap, how_many_packets, handler, handle_data);
#endif
    UNUSEDPARM(hPcap);UNUSEDPARM(how_many_packets);UNUSEDPARM(handler);UNUSEDPARM(handle_data);
    return 0;
}