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
 int pcap_minor_version (void*) ; 

__attribute__((used)) static int null_PCAP_MINOR_VERSION(void *p)
{
#ifdef STATICPCAP
    return pcap_minor_version(p);
#endif
    UNUSEDPARM(p);
    return 0;
}