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
 int /*<<< orphan*/ * my_null (int,char const*,char*) ; 
 int /*<<< orphan*/ * pcap_open_offline (char const*,char*) ; 

__attribute__((used)) static pcap_t *null_PCAP_OPEN_OFFLINE(const char *fname, char *errbuf)
{
#ifdef STATICPCAP
    return pcap_open_offline(fname, errbuf);
#endif
    return my_null(2, fname, errbuf);
}