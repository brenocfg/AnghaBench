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
struct TYPE_4__ {struct TYPE_4__* shape; struct TYPE_4__* format; } ;
typedef  TYPE_1__ _buffer_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void
_buffer_info_free(_buffer_info_t *info)
{
    if (info->format) {
        free(info->format);
    }
    if (info->shape) {
        free(info->shape);
    }
    free(info);
}