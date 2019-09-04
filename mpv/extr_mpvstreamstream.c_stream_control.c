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
struct TYPE_4__ {int (* control ) (TYPE_1__*,int,void*) ;} ;
typedef  TYPE_1__ stream_t ;

/* Variables and functions */
 int STREAM_UNSUPPORTED ; 
 int stub1 (TYPE_1__*,int,void*) ; 

int stream_control(stream_t *s, int cmd, void *arg)
{
    return s->control ? s->control(s, cmd, arg) : STREAM_UNSUPPORTED;
}