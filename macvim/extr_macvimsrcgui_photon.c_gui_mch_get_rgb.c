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
typedef  int /*<<< orphan*/  long_u ;
typedef  int /*<<< orphan*/  guicolor_T ;

/* Variables and functions */
 int /*<<< orphan*/  PgBlueValue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PgGreenValue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PgRGB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PgRedValue (int /*<<< orphan*/ ) ; 

long_u
gui_mch_get_rgb(guicolor_T pixel)
{
    return PgRGB(PgRedValue(pixel), PgGreenValue(pixel), PgBlueValue(pixel));
}