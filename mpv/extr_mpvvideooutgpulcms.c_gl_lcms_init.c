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
struct mpv_global {int dummy; } ;
struct mp_log {int dummy; } ;
struct mp_icc_opts {int dummy; } ;
struct gl_lcms {int dummy; } ;

/* Variables and functions */
 scalar_t__ talloc_new (void*) ; 

struct gl_lcms *gl_lcms_init(void *talloc_ctx, struct mp_log *log,
                             struct mpv_global *global,
                             struct mp_icc_opts *opts)
{
    return (struct gl_lcms *) talloc_new(talloc_ctx);
}