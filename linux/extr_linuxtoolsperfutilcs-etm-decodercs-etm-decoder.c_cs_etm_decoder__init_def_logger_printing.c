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
struct cs_etm_decoder_params {int /*<<< orphan*/ * packet_printer; } ;
struct cs_etm_decoder {int /*<<< orphan*/  dcd_tree; int /*<<< orphan*/ * packet_printer; } ;

/* Variables and functions */
 int /*<<< orphan*/  C_API_MSGLOGOUT_FLG_NONE ; 
 int /*<<< orphan*/  OCSD_ERR_SEV_ERROR ; 
 int /*<<< orphan*/  cs_etm_decoder__print_str_cb ; 
 int ocsd_def_errlog_config_output (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ocsd_def_errlog_init (int /*<<< orphan*/ ,int) ; 
 int ocsd_def_errlog_set_strprint_cb (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cs_etm_decoder__init_def_logger_printing(struct cs_etm_decoder_params *d_params,
					 struct cs_etm_decoder *decoder)
{
	int ret = 0;

	if (d_params->packet_printer == NULL)
		return -1;

	decoder->packet_printer = d_params->packet_printer;

	/*
	 * Set up a library default logger to process any printers
	 * (packet/raw frame) we add later.
	 */
	ret = ocsd_def_errlog_init(OCSD_ERR_SEV_ERROR, 1);
	if (ret != 0)
		return -1;

	/* no stdout / err / file output */
	ret = ocsd_def_errlog_config_output(C_API_MSGLOGOUT_FLG_NONE, NULL);
	if (ret != 0)
		return -1;

	/*
	 * Set the string CB for the default logger, passes strings to
	 * perf print logger.
	 */
	ret = ocsd_def_errlog_set_strprint_cb(decoder->dcd_tree,
					      (void *)decoder,
					      cs_etm_decoder__print_str_cb);
	if (ret != 0)
		ret = -1;

	return 0;
}