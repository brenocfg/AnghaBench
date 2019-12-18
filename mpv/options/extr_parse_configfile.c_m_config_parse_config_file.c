#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  log; } ;
typedef  TYPE_1__ m_config_t ;
struct TYPE_9__ {int /*<<< orphan*/  start; } ;
typedef  TYPE_2__ bstr ;

/* Variables and functions */
 int /*<<< orphan*/  MP_VERBOSE (TYPE_1__*,char*,char const*) ; 
 int M_SETOPT_FROM_CONFIG_FILE ; 
 int m_config_parse (TYPE_1__*,char const*,TYPE_2__,char*,int) ; 
 TYPE_2__ read_file (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ ) ; 

int m_config_parse_config_file(m_config_t *config, const char *conffile,
                               char *initial_section, int flags)
{
    flags = flags | M_SETOPT_FROM_CONFIG_FILE;

    MP_VERBOSE(config, "Reading config file %s\n", conffile);

    bstr data = read_file(config->log, conffile);
    if (!data.start)
        return 0;

    int r = m_config_parse(config, conffile, data, initial_section, flags);
    talloc_free(data.start);
    return r;
}