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
struct wined3d_cs {TYPE_1__* ops; } ;
typedef  enum wined3d_push_constants { ____Placeholder_wined3d_push_constants } wined3d_push_constants ;
struct TYPE_2__ {int /*<<< orphan*/  (* push_constants ) (struct wined3d_cs*,int,unsigned int,unsigned int,void const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct wined3d_cs*,int,unsigned int,unsigned int,void const*) ; 

__attribute__((used)) static inline void wined3d_cs_push_constants(struct wined3d_cs *cs, enum wined3d_push_constants p,
        unsigned int start_idx, unsigned int count, const void *constants)
{
    cs->ops->push_constants(cs, p, start_idx, count, constants);
}