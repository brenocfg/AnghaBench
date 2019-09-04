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
struct mp_filter {int dummy; } ;

/* Variables and functions */
 struct mp_filter* vf_d3d11vpp_create (struct mp_filter*,int /*<<< orphan*/ *) ; 

struct mp_filter *vf_d3d11_create_outconv(struct mp_filter *parent)
{
    // options==NULL is normally not allowed, and specially handled.
    return vf_d3d11vpp_create(parent, NULL);
}