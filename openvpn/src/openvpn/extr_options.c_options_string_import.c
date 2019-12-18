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
struct options {int dummy; } ;
struct env_set {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  read_config_string (char*,struct options*,char const*,int const,unsigned int const,unsigned int*,struct env_set*) ; 

void
options_string_import(struct options *options,
                      const char *config,
                      const int msglevel,
                      const unsigned int permission_mask,
                      unsigned int *option_types_found,
                      struct env_set *es)
{
    read_config_string("[CONFIG-STRING]", options, config, msglevel, permission_mask, option_types_found, es);
}