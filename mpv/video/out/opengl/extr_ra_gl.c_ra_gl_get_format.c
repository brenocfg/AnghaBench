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
struct ra_format {struct gl_format* priv; } ;
struct gl_format {int /*<<< orphan*/  type; int /*<<< orphan*/  format; int /*<<< orphan*/  internal_format; } ;
typedef  int /*<<< orphan*/  GLint ;
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */

void ra_gl_get_format(const struct ra_format *fmt, GLint *out_internal_format,
                      GLenum *out_format, GLenum *out_type)
{
    const struct gl_format *gl_format = fmt->priv;
    *out_internal_format = gl_format->internal_format;
    *out_format = gl_format->format;
    *out_type = gl_format->type;
}