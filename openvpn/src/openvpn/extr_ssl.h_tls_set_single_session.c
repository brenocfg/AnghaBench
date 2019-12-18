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
struct TYPE_2__ {int single_session; } ;
struct tls_multi {TYPE_1__ opt; } ;

/* Variables and functions */

__attribute__((used)) static inline void
tls_set_single_session(struct tls_multi *multi)
{
    if (multi)
    {
        multi->opt.single_session = true;
    }
}