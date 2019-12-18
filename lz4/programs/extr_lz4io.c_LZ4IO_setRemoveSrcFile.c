#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int removeSrcFile; } ;
typedef  TYPE_1__ LZ4IO_prefs_t ;

/* Variables and functions */

void LZ4IO_setRemoveSrcFile(LZ4IO_prefs_t* const prefs, unsigned flag)
{
  prefs->removeSrcFile = (flag>0);
}