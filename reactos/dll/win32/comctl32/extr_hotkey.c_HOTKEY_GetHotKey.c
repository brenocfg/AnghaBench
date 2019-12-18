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
struct TYPE_4__ {int /*<<< orphan*/  HotKey; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_1__ HOTKEY_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  HIBYTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOBYTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT
HOTKEY_GetHotKey(const HOTKEY_INFO *infoPtr)
{
    TRACE("(infoPtr=%p) Modifiers: 0x%x, Virtual Key: %d\n", infoPtr, 
          HIBYTE(infoPtr->HotKey), LOBYTE(infoPtr->HotKey));
    return (LRESULT)infoPtr->HotKey;
}