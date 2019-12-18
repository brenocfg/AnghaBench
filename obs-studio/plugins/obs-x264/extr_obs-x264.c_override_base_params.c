#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct obs_x264 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  override_base_param (struct obs_x264*,int /*<<< orphan*/ ,char**,char**,char**) ; 

__attribute__((used)) static inline void override_base_params(struct obs_x264 *obsx264, char **params,
					char **preset, char **profile,
					char **tune)
{
	while (*params)
		override_base_param(obsx264, *(params++), preset, profile,
				    tune);
}