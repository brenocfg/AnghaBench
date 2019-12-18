#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  sync; int /*<<< orphan*/  bound; int /*<<< orphan*/  connected; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_list_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_mutex_term (int /*<<< orphan*/ *) ; 
 TYPE_1__ self ; 

void nn_ins_term (void)
{
    nn_list_term (&self.connected);
    nn_list_term (&self.bound);
    nn_mutex_term (&self.sync);
}