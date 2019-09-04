#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {double timestamp; scalar_t__ cc_size; } ;
typedef  TYPE_1__ scc_t ;

/* Variables and functions */
 TYPE_1__* scc_relloc (int /*<<< orphan*/ ,int) ; 

scc_t* scc_new(int cc_count)
{
    scc_t* scc = scc_relloc(0, cc_count);
    scc->timestamp = 0.0;
    scc->cc_size = 0;
    return scc;
}