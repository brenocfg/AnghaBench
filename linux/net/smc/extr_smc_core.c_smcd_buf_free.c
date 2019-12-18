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
struct smcd_cdc_msg {int dummy; } ;
struct smc_link_group {int /*<<< orphan*/  smcd; } ;
struct smc_buf_desc {int len; struct smc_buf_desc* cpu_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct smc_buf_desc*) ; 
 int /*<<< orphan*/  smc_ism_unregister_dmb (int /*<<< orphan*/ ,struct smc_buf_desc*) ; 

__attribute__((used)) static void smcd_buf_free(struct smc_link_group *lgr, bool is_dmb,
			  struct smc_buf_desc *buf_desc)
{
	if (is_dmb) {
		/* restore original buf len */
		buf_desc->len += sizeof(struct smcd_cdc_msg);
		smc_ism_unregister_dmb(lgr->smcd, buf_desc);
	} else {
		kfree(buf_desc->cpu_addr);
	}
	kfree(buf_desc);
}