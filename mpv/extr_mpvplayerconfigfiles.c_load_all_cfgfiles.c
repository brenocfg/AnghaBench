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
struct MPContext {int /*<<< orphan*/  mconfig; int /*<<< orphan*/  global; } ;

/* Variables and functions */
 int /*<<< orphan*/  m_config_parse_config_file (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 char** mp_find_all_config_files (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  talloc_free (char**) ; 

__attribute__((used)) static void load_all_cfgfiles(struct MPContext *mpctx, char *section,
                              char *filename)
{
    char **cf = mp_find_all_config_files(NULL, mpctx->global, filename);
    for (int i = 0; cf && cf[i]; i++)
        m_config_parse_config_file(mpctx->mconfig, cf[i], section, 0);
    talloc_free(cf);
}