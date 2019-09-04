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
typedef  int uint ;
struct pwrctrl_priv {int alives; } ;

/* Variables and functions */

__attribute__((used)) static inline void unregister_task_alive(struct pwrctrl_priv *pwrctrl, uint tag)
{
	if (pwrctrl->alives & tag)
		pwrctrl->alives ^= tag;
}