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
struct dl_bw {int dummy; } ;
struct TYPE_3__ {struct dl_bw dl_bw; } ;
struct TYPE_4__ {TYPE_1__ dl; } ;

/* Variables and functions */
 TYPE_2__* cpu_rq (int) ; 

__attribute__((used)) static inline struct dl_bw *dl_bw_of(int i)
{
	return &cpu_rq(i)->dl.dl_bw;
}