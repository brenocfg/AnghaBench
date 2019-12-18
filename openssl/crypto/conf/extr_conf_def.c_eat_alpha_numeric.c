#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ flag_dollarid; } ;
typedef  TYPE_1__ CONF ;

/* Variables and functions */
 scalar_t__ IS_ALNUM_PUNCT (TYPE_1__*,char) ; 
 scalar_t__ IS_DOLLAR (TYPE_1__*,char) ; 
 scalar_t__ IS_ESC (TYPE_1__*,char) ; 
 char* scan_esc (TYPE_1__*,char*) ; 

__attribute__((used)) static char *eat_alpha_numeric(CONF *conf, char *p)
{
    for (;;) {
        if (IS_ESC(conf, *p)) {
            p = scan_esc(conf, p);
            continue;
        }
        if (!(IS_ALNUM_PUNCT(conf, *p)
              || (conf->flag_dollarid && IS_DOLLAR(conf, *p))))
            return p;
        p++;
    }
}