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
typedef  int /*<<< orphan*/  u8 ;
struct cflayer {int /*<<< orphan*/  (* ctrlcmd ) (struct cflayer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CAIF_CTRLCMD_INIT_FAIL_RSP ; 
 int /*<<< orphan*/  stub1 (struct cflayer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cfcnfg_reject_rsp(struct cflayer *layer, u8 channel_id,
			      struct cflayer *adapt_layer)
{
	if (adapt_layer != NULL && adapt_layer->ctrlcmd != NULL)
		adapt_layer->ctrlcmd(adapt_layer,
				     CAIF_CTRLCMD_INIT_FAIL_RSP, 0);
}