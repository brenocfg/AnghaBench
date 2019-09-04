#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* type; } ;
typedef  TYPE_2__ m_option_t ;
struct TYPE_6__ {char* (* pretty_print ) (TYPE_2__ const*,void const*) ;} ;

/* Variables and functions */
 char* m_option_print (TYPE_2__ const*,void const*) ; 
 char* stub1 (TYPE_2__ const*,void const*) ; 

__attribute__((used)) static inline char *m_option_pretty_print(const m_option_t *opt,
                                          const void *val_ptr)
{
    if (opt->type->pretty_print)
        return opt->type->pretty_print(opt, val_ptr);
    else
        return m_option_print(opt, val_ptr);
}