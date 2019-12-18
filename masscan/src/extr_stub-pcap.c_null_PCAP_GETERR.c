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
 int /*<<< orphan*/  UNUSEDPARM (int /*<<< orphan*/ *) ; 
 char const* pcap_geterr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char*null_PCAP_GETERR(pcap_t *p)
{
#ifdef STATICPCAP
    return pcap_geterr(p);
#endif
	UNUSEDPARM(p);
	return "(unknown)";
}