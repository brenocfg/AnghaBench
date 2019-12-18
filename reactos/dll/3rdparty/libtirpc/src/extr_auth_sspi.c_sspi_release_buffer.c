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
struct TYPE_3__ {scalar_t__ length; int /*<<< orphan*/ * value; } ;
typedef  TYPE_1__ sspi_buffer_desc ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void sspi_release_buffer(sspi_buffer_desc *buf)
{
    if (buf->value)
        free(buf->value);
    buf->value = NULL;
    buf->length = 0;
}