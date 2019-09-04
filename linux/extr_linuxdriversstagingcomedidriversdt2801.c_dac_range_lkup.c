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
struct comedi_lrange {int dummy; } ;

/* Variables and functions */
 struct comedi_lrange const** dac_range_table ; 
 struct comedi_lrange const range_unknown ; 

__attribute__((used)) static const struct comedi_lrange *dac_range_lkup(int opt)
{
	if (opt < 0 || opt >= 5)
		return &range_unknown;
	return dac_range_table[opt];
}