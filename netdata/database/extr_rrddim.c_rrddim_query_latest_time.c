#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_3__ {int /*<<< orphan*/  rrdset; } ;
typedef  TYPE_1__ RRDDIM ;

/* Variables and functions */
 int /*<<< orphan*/  rrdset_last_entry_t (int /*<<< orphan*/ ) ; 

__attribute__((used)) static time_t rrddim_query_latest_time(RRDDIM *rd) {
    return rrdset_last_entry_t(rd->rrdset);
}