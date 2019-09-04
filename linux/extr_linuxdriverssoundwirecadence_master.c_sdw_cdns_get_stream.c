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
typedef  scalar_t__ u32 ;
struct sdw_cdns_streams {int /*<<< orphan*/  num_bd; int /*<<< orphan*/  bd; int /*<<< orphan*/  num_out; int /*<<< orphan*/  out; int /*<<< orphan*/  num_in; int /*<<< orphan*/  in; } ;
struct sdw_cdns {int dummy; } ;

/* Variables and functions */
 scalar_t__ SDW_DATA_DIR_RX ; 
 int cdns_get_num_pdi (struct sdw_cdns*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

int sdw_cdns_get_stream(struct sdw_cdns *cdns,
			struct sdw_cdns_streams *stream,
			u32 ch, u32 dir)
{
	int pdis = 0;

	if (dir == SDW_DATA_DIR_RX)
		pdis = cdns_get_num_pdi(cdns, stream->in, stream->num_in, ch);
	else
		pdis = cdns_get_num_pdi(cdns, stream->out, stream->num_out, ch);

	/* check if we found PDI, else find in bi-directional */
	if (!pdis)
		pdis = cdns_get_num_pdi(cdns, stream->bd, stream->num_bd, ch);

	return pdis;
}