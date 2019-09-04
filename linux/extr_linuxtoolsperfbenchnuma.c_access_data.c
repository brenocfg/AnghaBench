#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct TYPE_3__ {scalar_t__ data_writes; scalar_t__ data_reads; } ;
struct TYPE_4__ {TYPE_1__ p; } ;

/* Variables and functions */
 TYPE_2__* g ; 

__attribute__((used)) static inline u64 access_data(u64 *data, u64 val)
{
	if (g->p.data_reads)
		val += *data;
	if (g->p.data_writes)
		*data = val + 1;
	return val;
}