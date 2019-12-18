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
struct gl_format {scalar_t__ type; int /*<<< orphan*/  format; } ;

/* Variables and functions */
 scalar_t__ GL_FLOAT ; 
 int MPGL_TYPE_FLOAT ; 
 int MPGL_TYPE_UINT ; 
 int MPGL_TYPE_UNORM ; 
 scalar_t__ gl_integer_format_to_base (int /*<<< orphan*/ ) ; 

int gl_format_type(const struct gl_format *format)
{
    if (!format)
        return 0;
    if (format->type == GL_FLOAT)
        return MPGL_TYPE_FLOAT;
    if (gl_integer_format_to_base(format->format))
        return MPGL_TYPE_UINT;
    return MPGL_TYPE_UNORM;
}