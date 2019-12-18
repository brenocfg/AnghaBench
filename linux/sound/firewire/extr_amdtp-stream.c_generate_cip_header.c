#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int fdf; } ;
struct TYPE_4__ {TYPE_1__ rx; } ;
struct amdtp_stream {unsigned int data_block_quadlets; unsigned int sph; unsigned int fmt; TYPE_2__ ctx_data; int /*<<< orphan*/  source_node_id_field; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 unsigned int CIP_DBS_SHIFT ; 
 unsigned int CIP_EOH ; 
 unsigned int CIP_FDF_MASK ; 
 unsigned int CIP_FDF_SHIFT ; 
 unsigned int CIP_FMT_MASK ; 
 unsigned int CIP_FMT_SHIFT ; 
 unsigned int CIP_SPH_MASK ; 
 unsigned int CIP_SPH_SHIFT ; 
 unsigned int CIP_SYT_MASK ; 
 unsigned int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (unsigned int) ; 

__attribute__((used)) static void generate_cip_header(struct amdtp_stream *s, __be32 cip_header[2],
			unsigned int data_block_counter, unsigned int syt)
{
	cip_header[0] = cpu_to_be32(READ_ONCE(s->source_node_id_field) |
				(s->data_block_quadlets << CIP_DBS_SHIFT) |
				((s->sph << CIP_SPH_SHIFT) & CIP_SPH_MASK) |
				data_block_counter);
	cip_header[1] = cpu_to_be32(CIP_EOH |
			((s->fmt << CIP_FMT_SHIFT) & CIP_FMT_MASK) |
			((s->ctx_data.rx.fdf << CIP_FDF_SHIFT) & CIP_FDF_MASK) |
			(syt & CIP_SYT_MASK));
}