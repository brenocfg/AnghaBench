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
struct image_writer_opts {int /*<<< orphan*/  format; } ;

/* Variables and functions */
 struct image_writer_opts image_writer_opts_defaults ; 
 char const* m_opt_choice_str (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_image_writer_formats ; 

const char *image_writer_file_ext(const struct image_writer_opts *opts)
{
    struct image_writer_opts defs = image_writer_opts_defaults;

    if (!opts)
        opts = &defs;

    return m_opt_choice_str(mp_image_writer_formats, opts->format);
}