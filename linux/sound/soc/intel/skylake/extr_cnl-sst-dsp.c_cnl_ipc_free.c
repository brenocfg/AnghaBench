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
struct sst_generic_ipc {int /*<<< orphan*/  dsp; } ;

/* Variables and functions */
 int /*<<< orphan*/  cnl_ipc_op_int_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_ipc_fini (struct sst_generic_ipc*) ; 

void cnl_ipc_free(struct sst_generic_ipc *ipc)
{
	cnl_ipc_op_int_disable(ipc->dsp);
	sst_ipc_fini(ipc);
}