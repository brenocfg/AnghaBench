#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* string; } ;
struct TYPE_5__ {TYPE_1__ data; } ;
typedef  TYPE_2__ json_stream ;

/* Variables and functions */
 double strtod (char*,int /*<<< orphan*/ *) ; 

double json_get_number(json_stream *json)
{
    char *p = json->data.string;
    return p == NULL ? 0 : strtod(p, NULL);
}