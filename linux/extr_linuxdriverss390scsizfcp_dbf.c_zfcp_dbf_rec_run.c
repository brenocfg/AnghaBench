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
struct zfcp_erp_action {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  zfcp_dbf_rec_run_lvl (int,char*,struct zfcp_erp_action*) ; 

void zfcp_dbf_rec_run(char *tag, struct zfcp_erp_action *erp)
{
	zfcp_dbf_rec_run_lvl(1, tag, erp);
}