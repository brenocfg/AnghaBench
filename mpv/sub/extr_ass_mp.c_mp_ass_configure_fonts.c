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
struct osd_style_opts {int font_provider; int /*<<< orphan*/  font; } ;
struct mpv_global {int dummy; } ;
struct mp_log {int dummy; } ;
typedef  int /*<<< orphan*/  ASS_Renderer ;

/* Variables and functions */
 int ASS_FONTPROVIDER_AUTODETECT ; 
 int ASS_FONTPROVIDER_FONTCONFIG ; 
 int ASS_FONTPROVIDER_NONE ; 
 int /*<<< orphan*/  ass_set_fonts (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,char*,int) ; 
 char* mp_find_config_file (void*,struct mpv_global*,char*) ; 
 int /*<<< orphan*/  mp_path_exists (char*) ; 
 int /*<<< orphan*/  mp_verbose (struct mp_log*,char*) ; 
 int /*<<< orphan*/  talloc_free (void*) ; 
 void* talloc_new (int /*<<< orphan*/ *) ; 

void mp_ass_configure_fonts(ASS_Renderer *priv, struct osd_style_opts *opts,
                            struct mpv_global *global, struct mp_log *log)
{
    void *tmp = talloc_new(NULL);
    char *default_font = mp_find_config_file(tmp, global, "subfont.ttf");
    char *config       = mp_find_config_file(tmp, global, "fonts.conf");

    if (default_font && !mp_path_exists(default_font))
        default_font = NULL;

    int font_provider = ASS_FONTPROVIDER_AUTODETECT;
    if (opts->font_provider == 1)
        font_provider = ASS_FONTPROVIDER_NONE;
    if (opts->font_provider == 2)
        font_provider = ASS_FONTPROVIDER_FONTCONFIG;

    mp_verbose(log, "Setting up fonts...\n");
    ass_set_fonts(priv, default_font, opts->font, font_provider, config, 1);
    mp_verbose(log, "Done.\n");

    talloc_free(tmp);
}