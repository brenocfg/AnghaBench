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
struct ctlr_info {int /*<<< orphan*/  sas_host; } ;

/* Variables and functions */
 int /*<<< orphan*/  hpsa_free_sas_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hpsa_delete_sas_host(struct ctlr_info *h)
{
	hpsa_free_sas_node(h->sas_host);
}