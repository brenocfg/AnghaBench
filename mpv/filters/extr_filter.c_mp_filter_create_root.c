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
struct mp_filter_params {struct mpv_global* global; int /*<<< orphan*/ * info; } ;
struct mp_filter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  filter_root ; 
 struct mp_filter* mp_filter_create_with_params (struct mp_filter_params*) ; 

struct mp_filter *mp_filter_create_root(struct mpv_global *global)
{
    struct mp_filter_params params = {
        .info = &filter_root,
        .global = global,
    };
    return mp_filter_create_with_params(&params);
}