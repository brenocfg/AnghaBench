#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  mmal_buffer_header_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_mmal_buffer(void *arg)
{
    MMAL_BUFFER_HEADER_T *buffer = arg;
    mmal_buffer_header_release(buffer);
}