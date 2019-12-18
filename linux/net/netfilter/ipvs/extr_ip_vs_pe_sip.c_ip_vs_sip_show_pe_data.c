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
struct ip_vs_conn {int pe_data_len; int /*<<< orphan*/  pe_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ip_vs_sip_show_pe_data(const struct ip_vs_conn *cp, char *buf)
{
	memcpy(buf, cp->pe_data, cp->pe_data_len);
	return cp->pe_data_len;
}