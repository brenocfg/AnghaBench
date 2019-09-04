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
struct ila_params {int dummy; } ;
struct TYPE_2__ {struct ila_params p; } ;

/* Variables and functions */
 TYPE_1__* ila_lwt_lwtunnel (struct lwtunnel_state*) ; 

__attribute__((used)) static inline struct ila_params *ila_params_lwtunnel(
	struct lwtunnel_state *lwt)
{
	return &ila_lwt_lwtunnel(lwt)->p;
}