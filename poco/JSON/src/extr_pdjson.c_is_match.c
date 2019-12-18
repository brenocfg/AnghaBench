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
struct TYPE_5__ {char const (* get ) (TYPE_2__*) ;} ;
struct TYPE_4__ {TYPE_2__ source; } ;
typedef  TYPE_1__ json_stream ;
typedef  enum json_type { ____Placeholder_json_type } json_type ;

/* Variables and functions */
 int JSON_ERROR ; 
 char const stub1 (TYPE_2__*) ; 

__attribute__((used)) static enum json_type
is_match(json_stream *json, const char *pattern, enum json_type type)
{
    for (const char *p = pattern; *p; p++)
        if (*p != json->source.get(&json->source))
            return JSON_ERROR;
    return type;
}