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
struct TYPE_4__ {int (* get_size ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ stream_t ;
typedef  int int64_t ;

/* Variables and functions */
 int stub1 (TYPE_1__*) ; 

int64_t stream_get_size(stream_t *s)
{
    return s->get_size ? s->get_size(s) : -1;
}