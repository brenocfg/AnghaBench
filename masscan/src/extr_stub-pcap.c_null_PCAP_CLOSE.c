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

/* Variables and functions */
 int /*<<< orphan*/  UNUSEDPARM (void*) ; 
 int /*<<< orphan*/  pcap_close (void*) ; 

__attribute__((used)) static void null_PCAP_CLOSE(void *hPcap)
{
#ifdef STATICPCAP
    pcap_close(hPcap);
    return;
#endif
    UNUSEDPARM(hPcap);
}