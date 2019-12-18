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
struct TYPE_3__ {int flags; char const* errmsg; } ;
typedef  TYPE_1__ json_stream ;

/* Variables and functions */
 int JSON_FLAG_ERROR ; 

const char *json_get_error(json_stream *json)
{
    return json->flags & JSON_FLAG_ERROR ? json->errmsg : NULL;
}