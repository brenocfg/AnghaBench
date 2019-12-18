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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ LONG ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ find_prev_space (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ isspaceW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  move_next_char (int /*<<< orphan*/ *) ; 

__attribute__((used)) static LONG move_by_words(rangepoint_t *iter, LONG cnt)
{
    LONG ret = 0;

    if(cnt >= 0) {
        WCHAR c;

        while(ret < cnt && (c = move_next_char(iter))) {
            if(isspaceW(c))
                ret++;
        }
    }else {
        while(ret > cnt && find_prev_space(iter, FALSE))
            ret--;
    }

    return ret;
}