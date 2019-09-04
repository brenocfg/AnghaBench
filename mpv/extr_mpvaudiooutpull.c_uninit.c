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
struct ao_pull_state {int /*<<< orphan*/  convert_buffer; } ;
struct ao {TYPE_1__* driver; struct ao_pull_state* api_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* uninit ) (struct ao*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ao*) ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uninit(struct ao *ao)
{
    struct ao_pull_state *p = ao->api_priv;

    ao->driver->uninit(ao);

    talloc_free(p->convert_buffer);
}