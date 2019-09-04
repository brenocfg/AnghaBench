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
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
#define  STREAM_CTRL_GET_SIZE 128 
 int STREAM_UNSUPPORTED ; 
 int /*<<< orphan*/  get_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int control(stream_t *s, int cmd, void *arg)
{
    switch (cmd) {
    case STREAM_CTRL_GET_SIZE: {
        int64_t size = get_size(s);
        if (size >= 0) {
            *(int64_t *)arg = size;
            return 1;
        }
        break;
    }
    }
    return STREAM_UNSUPPORTED;
}