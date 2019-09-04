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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_TUNER_FREQ ; 
 int /*<<< orphan*/  hpi_control_query (int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ *) ; 

u16 hpi_tuner_query_frequency(const u32 h_tuner, const u32 index,
	const u16 band, u32 *pfreq)
{
	return hpi_control_query(h_tuner, HPI_TUNER_FREQ, index, band, pfreq);
}