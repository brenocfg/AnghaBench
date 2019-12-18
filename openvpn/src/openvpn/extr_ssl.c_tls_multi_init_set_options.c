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
struct TYPE_2__ {char const* local_options; char const* remote_options; } ;
struct tls_multi {TYPE_1__ opt; } ;

/* Variables and functions */

void
tls_multi_init_set_options(struct tls_multi *multi,
                           const char *local,
                           const char *remote)
{
#ifdef ENABLE_OCC
    /* initialize options string */
    multi->opt.local_options = local;
    multi->opt.remote_options = remote;
#endif
}