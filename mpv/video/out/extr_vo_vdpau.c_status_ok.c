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
struct vo {scalar_t__ config_ok; } ;

/* Variables and functions */
 scalar_t__ check_preemption (struct vo*) ; 

__attribute__((used)) static bool status_ok(struct vo *vo)
{
    return vo->config_ok && check_preemption(vo);
}