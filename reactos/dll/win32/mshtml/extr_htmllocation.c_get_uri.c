#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* window; } ;
struct TYPE_7__ {TYPE_1__* outer_window; } ;
struct TYPE_8__ {TYPE_2__ base; } ;
struct TYPE_6__ {int /*<<< orphan*/ * uri; } ;
typedef  int /*<<< orphan*/  IUri ;
typedef  TYPE_4__ HTMLLocation ;

/* Variables and functions */

__attribute__((used)) static IUri *get_uri(HTMLLocation *This)
{
    if(!This->window || !This->window->base.outer_window)
        return NULL;
    return This->window->base.outer_window->uri;
}