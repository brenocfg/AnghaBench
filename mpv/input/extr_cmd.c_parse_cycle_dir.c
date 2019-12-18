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
struct mp_log {int dummy; } ;
struct m_option {int dummy; } ;
struct bstr {int dummy; } ;
struct TYPE_2__ {int (* parse ) (struct mp_log*,struct m_option const*,struct bstr,struct bstr,void*) ;} ;

/* Variables and functions */
 scalar_t__ bstrcmp0 (struct bstr,char*) ; 
 TYPE_1__ m_option_type_double ; 
 int stub1 (struct mp_log*,struct m_option const*,struct bstr,struct bstr,void*) ; 

__attribute__((used)) static int parse_cycle_dir(struct mp_log *log, const struct m_option *opt,
                           struct bstr name, struct bstr param, void *dst)
{
    double val;
    if (bstrcmp0(param, "up") == 0) {
        val = +1;
    } else if (bstrcmp0(param, "down") == 0) {
        val = -1;
    } else {
        return m_option_type_double.parse(log, opt, name, param, dst);
    }
    *(double *)dst = val;
    return 1;
}