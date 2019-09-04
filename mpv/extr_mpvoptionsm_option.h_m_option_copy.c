#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* type; } ;
typedef  TYPE_2__ m_option_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* copy ) (TYPE_2__ const*,void*,void const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__ const*,void*,void const*) ; 

__attribute__((used)) static inline void m_option_copy(const m_option_t *opt, void *dst,
                                 const void *src)
{
    if (opt->type->copy)
        opt->type->copy(opt, dst, src);
}