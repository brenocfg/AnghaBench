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
typedef  scalar_t__ sa_family_t ;
struct TYPE_3__ {scalar_t__ proto_af; int proto; char const* display_form; char const* short_form; } ;

/* Variables and functions */
 unsigned int SIZE (TYPE_1__*) ; 
 TYPE_1__* proto_names ; 

const char *
proto2ascii(int proto, sa_family_t af, bool display_form)
{
    unsigned int i;
    for (i = 0; i < SIZE(proto_names); ++i)
    {
        if (proto_names[i].proto_af == af && proto_names[i].proto == proto)
        {
            if (display_form)
            {
                return proto_names[i].display_form;
            }
            else
            {
                return proto_names[i].short_form;
            }
        }
    }

    return "[unknown protocol]";
}