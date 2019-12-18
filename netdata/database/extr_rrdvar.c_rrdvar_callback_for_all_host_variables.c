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
struct TYPE_3__ {int /*<<< orphan*/  rrdvar_root_index; } ;
typedef  TYPE_1__ RRDHOST ;

/* Variables and functions */
 int avl_traverse_lock (int /*<<< orphan*/ *,int (*) (void*,void*),void*) ; 

inline int rrdvar_callback_for_all_host_variables(RRDHOST *host, int (*callback)(void * /*rrdvar*/, void * /*data*/), void *data) {
    return avl_traverse_lock(&host->rrdvar_root_index, callback, data);
}