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
struct hdspm {int period_bytes; } ;

/* Variables and functions */
 int hdspm_get_latency (struct hdspm*) ; 

__attribute__((used)) static inline void hdspm_compute_period_size(struct hdspm *hdspm)
{
	hdspm->period_bytes = 4 * hdspm_get_latency(hdspm);
}