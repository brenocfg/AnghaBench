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
typedef  size_t u32 ;
struct TYPE_2__ {int /*<<< orphan*/  out_base; } ;
struct sst_dsp {TYPE_1__ mailbox; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy_fromio (void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  trace_sst_ipc_outbox_rdata (size_t,size_t) ; 
 int /*<<< orphan*/  trace_sst_ipc_outbox_read (size_t) ; 

void sst_dsp_outbox_read(struct sst_dsp *sst, void *message, size_t bytes)
{
	u32 i;

	trace_sst_ipc_outbox_read(bytes);

	memcpy_fromio(message, sst->mailbox.out_base, bytes);

	for (i = 0; i < bytes; i += 4)
		trace_sst_ipc_outbox_rdata(i, *(u32 *)(message + i));
}