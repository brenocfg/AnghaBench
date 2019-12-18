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
typedef  int /*<<< orphan*/  tilegx_pipeline ;
struct tilegx_opcode {int pipes; } ;

/* Variables and functions */
 int TILEGX_NUM_PIPELINE_ENCODINGS ; 

tilegx_pipeline get_any_valid_pipe(const struct tilegx_opcode* opcode)
{
	/* FIXME: tile: we could pregenerate this. */
	int pipe;
	for (pipe = 0; ((opcode->pipes & (1 << pipe)) == 0 && pipe < TILEGX_NUM_PIPELINE_ENCODINGS); pipe++)
		;
	return (tilegx_pipeline)(pipe);
}