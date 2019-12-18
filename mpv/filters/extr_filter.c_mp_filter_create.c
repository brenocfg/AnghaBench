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
struct mp_filter_params {struct mp_filter_info const* parent; struct mp_filter_info const* info; } ;
struct mp_filter_info {int dummy; } ;
typedef  struct mp_filter_info const mp_filter ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct mp_filter_info const*) ; 
 struct mp_filter_info const* mp_filter_create_with_params (struct mp_filter_params*) ; 

struct mp_filter *mp_filter_create(struct mp_filter *parent,
                                   const struct mp_filter_info *info)
{
    assert(parent);
    assert(info);
    struct mp_filter_params params = {
        .info = info,
        .parent = parent,
    };
    return mp_filter_create_with_params(&params);
}