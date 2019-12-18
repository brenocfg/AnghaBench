#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int X; int Y; } ;
struct TYPE_5__ {TYPE_1__ dwMaximumWindowSize; } ;
typedef  TYPE_2__ CONSOLE_SCREEN_BUFFER_INFO ;

/* Variables and functions */
 scalar_t__ GetConsoleScreenBufferInfo (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  GetStdHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STD_OUTPUT_HANDLE ; 

void terminal_get_size(int *w, int *h)
{
    CONSOLE_SCREEN_BUFFER_INFO cinfo;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cinfo)) {
        *w = cinfo.dwMaximumWindowSize.X - 1;
        *h = cinfo.dwMaximumWindowSize.Y;
    }
}