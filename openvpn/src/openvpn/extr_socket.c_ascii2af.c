#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sa_family_t ;
struct TYPE_3__ {int /*<<< orphan*/  proto_af; int /*<<< orphan*/  short_form; } ;

/* Variables and functions */
 int SIZE (TYPE_1__*) ; 
 TYPE_1__* proto_names ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

sa_family_t
ascii2af(const char *proto_name)
{
    int i;
    for (i = 0; i < SIZE(proto_names); ++i)
    {
        if (!strcmp(proto_name, proto_names[i].short_form))
        {
            return proto_names[i].proto_af;
        }
    }
    return 0;
}