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
struct config_line {int dummy; } ;
struct config {int /*<<< orphan*/  parser; scalar_t__ error_message; } ;

/* Variables and functions */
 struct config_line const* parser_next (int /*<<< orphan*/ *) ; 

const struct config_line *config_read_line(struct config *conf)
{
    return conf->error_message ? NULL : parser_next(&conf->parser);
}