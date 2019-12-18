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
struct hdspm {scalar_t__ io_type; int /*<<< orphan*/  control_register; } ;

/* Variables and functions */
 scalar_t__ AIO ; 
 scalar_t__ RayDAT ; 
 int hdspm_decode_latency (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hdspm_get_latency(struct hdspm *hdspm)
{
	int n;

	n = hdspm_decode_latency(hdspm->control_register);

	/* Special case for new RME cards with 32 samples period size.
	 * The three latency bits in the control register
	 * (HDSP_LatencyMask) encode latency values of 64 samples as
	 * 0, 128 samples as 1 ... 4096 samples as 6. For old cards, 7
	 * denotes 8192 samples, but on new cards like RayDAT or AIO,
	 * it corresponds to 32 samples.
	 */
	if ((7 == n) && (RayDAT == hdspm->io_type || AIO == hdspm->io_type))
		n = -1;

	return 1 << (n + 6);
}