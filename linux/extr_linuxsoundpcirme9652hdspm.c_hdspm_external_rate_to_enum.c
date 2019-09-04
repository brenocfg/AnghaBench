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
struct hdspm {int dummy; } ;

/* Variables and functions */
 int HDSPM_bit2freq (int) ; 
 int hdspm_external_sample_rate (struct hdspm*) ; 

__attribute__((used)) static int hdspm_external_rate_to_enum(struct hdspm *hdspm)
{
	int rate = hdspm_external_sample_rate(hdspm);
	int i, selected_rate = 0;
	for (i = 1; i < 10; i++)
		if (HDSPM_bit2freq(i) == rate) {
			selected_rate = i;
			break;
		}
	return selected_rate;
}