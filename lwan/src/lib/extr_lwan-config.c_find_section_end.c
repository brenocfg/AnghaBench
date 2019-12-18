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
struct config_line {scalar_t__ type; } ;
struct config {int /*<<< orphan*/  parser; scalar_t__ error_message; } ;

/* Variables and functions */
 scalar_t__ CONFIG_LINE_TYPE_SECTION ; 
 scalar_t__ CONFIG_LINE_TYPE_SECTION_END ; 
 struct config_line* parser_next (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool find_section_end(struct config *config)
{
    const struct config_line *line;
    int cur_level = 1;

    if (config->error_message)
        return false;

    while ((line = parser_next(&config->parser))) {
        if (line->type == CONFIG_LINE_TYPE_SECTION) {
            cur_level++;
        } else if (line->type == CONFIG_LINE_TYPE_SECTION_END) {
            cur_level--;

            if (!cur_level)
                return true;
        }
    }

    return false;
}