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
struct TYPE_4__ {char* text; int line; int column; char* source; scalar_t__ position; } ;
typedef  TYPE_1__ json_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  jsonp_error_set_source (TYPE_1__*,char const*) ; 

void jsonp_error_init(json_error_t *error, const char *source)
{
    if(error)
    {
        error->text[0] = '\0';
        error->line = -1;
        error->column = -1;
        error->position = 0;
        if(source)
            jsonp_error_set_source(error, source);
        else
            error->source[0] = '\0';
    }
}