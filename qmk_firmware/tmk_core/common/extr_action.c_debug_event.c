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
struct TYPE_4__ {int row; int col; } ;
struct TYPE_5__ {int /*<<< orphan*/  time; scalar_t__ pressed; TYPE_1__ key; } ;
typedef  TYPE_2__ keyevent_t ;

/* Variables and functions */
 int /*<<< orphan*/  dprintf (char*,int,char,int /*<<< orphan*/ ) ; 

void debug_event(keyevent_t event) { dprintf("%04X%c(%u)", (event.key.row << 8 | event.key.col), (event.pressed ? 'd' : 'u'), event.time); }