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
struct cs_etm_decoder {int /*<<< orphan*/  dcd_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCSD_CREATE_FLG_PACKET_PROC ; 
 scalar_t__ ocsd_dt_create_decoder (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 scalar_t__ ocsd_dt_set_pkt_protocol_printer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cs_etm_decoder__create_packet_printer(struct cs_etm_decoder *decoder,
						 const char *decoder_name,
						 void *trace_config)
{
	u8 csid;

	if (ocsd_dt_create_decoder(decoder->dcd_tree, decoder_name,
				   OCSD_CREATE_FLG_PACKET_PROC,
				   trace_config, &csid))
		return -1;

	if (ocsd_dt_set_pkt_protocol_printer(decoder->dcd_tree, csid, 0))
		return -1;

	return 0;
}