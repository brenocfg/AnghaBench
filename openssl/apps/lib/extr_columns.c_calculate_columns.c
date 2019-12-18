#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int width; int columns; } ;
struct TYPE_5__ {scalar_t__ type; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ FUNCTION ;
typedef  TYPE_2__ DISPLAY_COLUMNS ;

/* Variables and functions */
 scalar_t__ FT_cipher ; 
 scalar_t__ FT_general ; 
 scalar_t__ FT_md ; 
 int strlen (int /*<<< orphan*/ *) ; 

void calculate_columns(FUNCTION *functions, DISPLAY_COLUMNS *dc)
{
    FUNCTION *f;
    int len, maxlen = 0;

    for (f = functions; f->name != NULL; ++f)
        if (f->type == FT_general || f->type == FT_md || f->type == FT_cipher)
            if ((len = strlen(f->name)) > maxlen)
                maxlen = len;

    dc->width = maxlen + 2;
    dc->columns = (80 - 1) / dc->width;
}