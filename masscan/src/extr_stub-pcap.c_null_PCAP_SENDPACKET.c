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
typedef  int /*<<< orphan*/  pcap_t ;

/* Variables and functions */
 int /*<<< orphan*/  my_null (int,int /*<<< orphan*/ *,unsigned char const*,int) ; 
 int pcap_sendpacket (int /*<<< orphan*/ *,unsigned char const*,int) ; 

__attribute__((used)) static int null_PCAP_SENDPACKET(pcap_t *p, const unsigned char *buf, int size)
{
#ifdef STATICPCAP
    return pcap_sendpacket(p, buf, size);
#endif
    my_null(3, p, buf, size);
	return 0;
}