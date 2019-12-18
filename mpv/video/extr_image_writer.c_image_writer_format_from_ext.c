#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int value; scalar_t__ name; } ;

/* Variables and functions */
 TYPE_1__* mp_image_writer_formats ; 
 scalar_t__ strcmp (scalar_t__,char const*) ; 

int image_writer_format_from_ext(const char *ext)
{
    for (int n = 0; mp_image_writer_formats[n].name; n++) {
        if (ext && strcmp(mp_image_writer_formats[n].name, ext) == 0)
            return mp_image_writer_formats[n].value;
    }
    return 0;
}