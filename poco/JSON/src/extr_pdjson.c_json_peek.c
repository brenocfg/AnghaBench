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
struct TYPE_4__ {int next; } ;
typedef  TYPE_1__ json_stream ;
typedef  enum json_type { ____Placeholder_json_type } json_type ;

/* Variables and functions */
 int json_next (TYPE_1__*) ; 

enum json_type json_peek(json_stream *json)
{
    enum json_type next = json_next(json);
    json->next = next;
    return next;
}