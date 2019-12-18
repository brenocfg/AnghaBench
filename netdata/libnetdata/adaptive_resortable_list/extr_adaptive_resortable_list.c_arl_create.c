#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void (* processor ) (char const*,uint32_t,char const*,void*) ;size_t rechecks; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ ARL_BASE ;

/* Variables and functions */
 void arl_callback_str2ull (char const*,uint32_t,char const*,void*) ; 
 TYPE_1__* callocz (int,int) ; 
 int /*<<< orphan*/  strdupz (char const*) ; 

ARL_BASE *arl_create(const char *name, void (*processor)(const char *, uint32_t, const char *, void *), size_t rechecks) {
    ARL_BASE *base = callocz(1, sizeof(ARL_BASE));

    base->name = strdupz(name);

    if(!processor)
        base->processor = arl_callback_str2ull;
    else
        base->processor = processor;

    base->rechecks = rechecks;

    return base;
}