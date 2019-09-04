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
struct wsm_reset {int reset_statistics; } ;
struct cw1200_common {int dummy; } ;

/* Variables and functions */
 int wsm_reset (struct cw1200_common*,struct wsm_reset*) ; 

int cw1200_disable_listening(struct cw1200_common *priv)
{
	int ret;
	struct wsm_reset reset = {
		.reset_statistics = true,
	};
	ret = wsm_reset(priv, &reset);
	return ret;
}