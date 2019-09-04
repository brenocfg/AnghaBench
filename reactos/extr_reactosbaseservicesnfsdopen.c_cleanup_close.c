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
struct TYPE_3__ {int /*<<< orphan*/  state_ref; } ;
typedef  TYPE_1__ nfs41_upcall ;

/* Variables and functions */
 int /*<<< orphan*/  nfs41_open_state_deref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cleanup_close(nfs41_upcall *upcall)
{
    /* release the initial reference from create_open_state() */
    nfs41_open_state_deref(upcall->state_ref);
}