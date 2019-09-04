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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  reg_traceidr; int /*<<< orphan*/  reg_configr; int /*<<< orphan*/  reg_idr8; int /*<<< orphan*/  reg_idr2; int /*<<< orphan*/  reg_idr1; int /*<<< orphan*/  reg_idr0; } ;
struct cs_etm_trace_params {TYPE_1__ etmv4; int /*<<< orphan*/  protocol; } ;
struct cs_etm_decoder_params {int formatted; int fsyncs; int hsyncs; int frame_aligned; int /*<<< orphan*/  operation; int /*<<< orphan*/  packet_printer; } ;
struct cs_etm_decoder {int dummy; } ;
struct cs_etm_auxtrace {int num_cpu; int /*<<< orphan*/ ** metadata; } ;
struct auxtrace_buffer {size_t size; scalar_t__ data; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 size_t CS_ETMV4_TRCCONFIGR ; 
 size_t CS_ETMV4_TRCIDR0 ; 
 size_t CS_ETMV4_TRCIDR1 ; 
 size_t CS_ETMV4_TRCIDR2 ; 
 size_t CS_ETMV4_TRCIDR8 ; 
 size_t CS_ETMV4_TRCTRACEIDR ; 
 int /*<<< orphan*/  CS_ETM_OPERATION_PRINT ; 
 int /*<<< orphan*/  CS_ETM_PROTO_ETMV4i ; 
 char* PERF_COLOR_BLUE ; 
 int /*<<< orphan*/  color_fprintf (int /*<<< orphan*/ ,char const*,char*,size_t) ; 
 int /*<<< orphan*/  cs_etm__packet_dump ; 
 int /*<<< orphan*/  cs_etm_decoder__free (struct cs_etm_decoder*) ; 
 struct cs_etm_decoder* cs_etm_decoder__new (int,struct cs_etm_decoder_params*,struct cs_etm_trace_params*) ; 
 int cs_etm_decoder__process_data_block (struct cs_etm_decoder*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,size_t*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stdout ; 
 struct cs_etm_trace_params* zalloc (int) ; 
 int /*<<< orphan*/  zfree (struct cs_etm_trace_params**) ; 

__attribute__((used)) static void cs_etm__dump_event(struct cs_etm_auxtrace *etm,
			       struct auxtrace_buffer *buffer)
{
	int i, ret;
	const char *color = PERF_COLOR_BLUE;
	struct cs_etm_decoder_params d_params;
	struct cs_etm_trace_params *t_params;
	struct cs_etm_decoder *decoder;
	size_t buffer_used = 0;

	fprintf(stdout, "\n");
	color_fprintf(stdout, color,
		     ". ... CoreSight ETM Trace data: size %zu bytes\n",
		     buffer->size);

	/* Use metadata to fill in trace parameters for trace decoder */
	t_params = zalloc(sizeof(*t_params) * etm->num_cpu);
	for (i = 0; i < etm->num_cpu; i++) {
		t_params[i].protocol = CS_ETM_PROTO_ETMV4i;
		t_params[i].etmv4.reg_idr0 = etm->metadata[i][CS_ETMV4_TRCIDR0];
		t_params[i].etmv4.reg_idr1 = etm->metadata[i][CS_ETMV4_TRCIDR1];
		t_params[i].etmv4.reg_idr2 = etm->metadata[i][CS_ETMV4_TRCIDR2];
		t_params[i].etmv4.reg_idr8 = etm->metadata[i][CS_ETMV4_TRCIDR8];
		t_params[i].etmv4.reg_configr =
					etm->metadata[i][CS_ETMV4_TRCCONFIGR];
		t_params[i].etmv4.reg_traceidr =
					etm->metadata[i][CS_ETMV4_TRCTRACEIDR];
	}

	/* Set decoder parameters to simply print the trace packets */
	d_params.packet_printer = cs_etm__packet_dump;
	d_params.operation = CS_ETM_OPERATION_PRINT;
	d_params.formatted = true;
	d_params.fsyncs = false;
	d_params.hsyncs = false;
	d_params.frame_aligned = true;

	decoder = cs_etm_decoder__new(etm->num_cpu, &d_params, t_params);

	zfree(&t_params);

	if (!decoder)
		return;
	do {
		size_t consumed;

		ret = cs_etm_decoder__process_data_block(
				decoder, buffer->offset,
				&((u8 *)buffer->data)[buffer_used],
				buffer->size - buffer_used, &consumed);
		if (ret)
			break;

		buffer_used += consumed;
	} while (buffer_used < buffer->size);

	cs_etm_decoder__free(decoder);
}