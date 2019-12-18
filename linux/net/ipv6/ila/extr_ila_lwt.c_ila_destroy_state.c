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
struct lwtunnel_state {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dst_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  dst_cache_destroy (int /*<<< orphan*/ *) ; 
 TYPE_1__* ila_lwt_lwtunnel (struct lwtunnel_state*) ; 

__attribute__((used)) static void ila_destroy_state(struct lwtunnel_state *lwt)
{
	dst_cache_destroy(&ila_lwt_lwtunnel(lwt)->dst_cache);
}