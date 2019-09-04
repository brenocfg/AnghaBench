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
struct fw_unit {int dummy; } ;
struct amdtp_stream {int dummy; } ;
struct amdtp_ff {int dummy; } ;
typedef  enum amdtp_stream_direction { ____Placeholder_amdtp_stream_direction } amdtp_stream_direction ;
typedef  int /*<<< orphan*/  amdtp_stream_process_data_blocks_t ;

/* Variables and functions */
 int AMDTP_IN_STREAM ; 
 int /*<<< orphan*/  CIP_NO_HEADER ; 
 int amdtp_stream_init (struct amdtp_stream*,struct fw_unit*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  process_rx_data_blocks ; 
 int /*<<< orphan*/  process_tx_data_blocks ; 

int amdtp_ff_init(struct amdtp_stream *s, struct fw_unit *unit,
		  enum amdtp_stream_direction dir)
{
	amdtp_stream_process_data_blocks_t process_data_blocks;

	if (dir == AMDTP_IN_STREAM)
		process_data_blocks = process_tx_data_blocks;
	else
		process_data_blocks = process_rx_data_blocks;

	return amdtp_stream_init(s, unit, dir, CIP_NO_HEADER, 0,
				 process_data_blocks, sizeof(struct amdtp_ff));
}