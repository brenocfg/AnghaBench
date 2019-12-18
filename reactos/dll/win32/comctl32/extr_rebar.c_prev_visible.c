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
typedef  int /*<<< orphan*/  REBAR_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  HIDDENBAND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REBAR_GetBand (int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int prev_visible(const REBAR_INFO *infoPtr, int i)
{
    int n;
    for (n = i - 1; n >= 0; n--)
        if (!HIDDENBAND(REBAR_GetBand(infoPtr, n)))
            break;
    return n;
}