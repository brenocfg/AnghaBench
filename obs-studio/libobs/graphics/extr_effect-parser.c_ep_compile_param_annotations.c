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
struct TYPE_4__ {int /*<<< orphan*/  da; } ;
struct gs_effect_param {TYPE_2__ annotations; } ;
struct TYPE_3__ {int /*<<< orphan*/  da; } ;
struct ep_param {TYPE_1__ annotations; } ;
struct effect_parser {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ep_compile_annotations (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct effect_parser*) ; 

__attribute__((used)) static void
ep_compile_param_annotations(struct ep_param *ep_param_input,
			     struct gs_effect_param *gs_effect_input,
			     struct effect_parser *ep)
{
	ep_compile_annotations(&(ep_param_input->annotations.da),
			       &(gs_effect_input->annotations.da), ep);
}