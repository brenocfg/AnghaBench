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
 int /*<<< orphan*/  my_null (int,int) ; 
 char const* pcap_datalink_val_toName (int) ; 

__attribute__((used)) static const char *null_PCAP_DATALINK_VAL_TO_NAME(int dlt)
{
#ifdef STATICPCAP
    return pcap_datalink_val_toName(dlt);
#endif
	my_null(1, dlt);
    return 0;
}