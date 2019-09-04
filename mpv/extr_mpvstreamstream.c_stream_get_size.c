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
typedef  int /*<<< orphan*/  stream_t ;
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  STREAM_CTRL_GET_SIZE ; 
 scalar_t__ STREAM_OK ; 
 scalar_t__ stream_control (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

int64_t stream_get_size(stream_t *s)
{
    int64_t size = -1;
    if (stream_control(s, STREAM_CTRL_GET_SIZE, &size) != STREAM_OK)
        size = -1;
    return size;
}