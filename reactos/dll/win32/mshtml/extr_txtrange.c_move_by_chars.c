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
typedef  int /*<<< orphan*/  rangepoint_t ;
typedef  scalar_t__ LONG ;

/* Variables and functions */
 scalar_t__ move_next_char (int /*<<< orphan*/ *) ; 
 scalar_t__ move_prev_char (int /*<<< orphan*/ *) ; 

__attribute__((used)) static LONG move_by_chars(rangepoint_t *iter, LONG cnt)
{
    LONG ret = 0;

    if(cnt >= 0) {
        while(ret < cnt && move_next_char(iter))
            ret++;
    }else {
        while(ret > cnt && move_prev_char(iter))
            ret--;
    }

    return ret;
}