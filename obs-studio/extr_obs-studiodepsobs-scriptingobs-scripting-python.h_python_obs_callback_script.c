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
struct TYPE_2__ {scalar_t__ script; } ;
struct python_obs_callback {TYPE_1__ base; } ;
struct obs_python_script {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct obs_python_script *python_obs_callback_script(
		struct python_obs_callback *cb)
{
	return (struct obs_python_script *)cb->base.script;
}