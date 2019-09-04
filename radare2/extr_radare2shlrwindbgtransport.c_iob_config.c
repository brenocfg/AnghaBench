#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int (* config ) (void*,void*) ;} ;

/* Variables and functions */
 int E_NOIF ; 
 TYPE_1__* sel_backend ; 
 int stub1 (void*,void*) ; 

int iob_config(void *fp, void *cfg) {
	if (!sel_backend) {
		return E_NOIF;
	}
	return sel_backend->config (fp, cfg);
}