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

/* Variables and functions */
 int MP_MAX_KEY_DOWN ; 

__attribute__((used)) static void key_buf_add(int *buf, int code)
{
    for (int n = MP_MAX_KEY_DOWN - 1; n > 0; n--)
        buf[n] = buf[n - 1];
    buf[0] = code;
}