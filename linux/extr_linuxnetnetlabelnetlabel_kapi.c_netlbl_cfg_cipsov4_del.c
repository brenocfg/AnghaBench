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
struct netlbl_audit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cipso_v4_doi_remove (int /*<<< orphan*/ ,struct netlbl_audit*) ; 

void netlbl_cfg_cipsov4_del(u32 doi, struct netlbl_audit *audit_info)
{
	cipso_v4_doi_remove(doi, audit_info);
}