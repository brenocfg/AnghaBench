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
typedef  int /*<<< orphan*/  u32 ;
struct ip_vs_conn_param {int /*<<< orphan*/  pe_data_len; int /*<<< orphan*/  pe_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  jhash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 ip_vs_sip_hashkey_raw(const struct ip_vs_conn_param *p,
				 u32 initval, bool inverse)
{
	return jhash(p->pe_data, p->pe_data_len, initval);
}