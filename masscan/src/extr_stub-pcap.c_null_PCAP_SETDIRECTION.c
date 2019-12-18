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
typedef  int /*<<< orphan*/  pcap_direction_t ;

/* Variables and functions */
 int /*<<< orphan*/  my_null (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pcap_setdirection (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int null_PCAP_SETDIRECTION(pcap_t *p, pcap_direction_t d)
{
#ifdef STATICPCAP
    return pcap_setdirection(p, d);
#endif
	my_null(2, p, d);
    return 0;
}