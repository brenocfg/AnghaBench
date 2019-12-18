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
struct mpv_global {int dummy; } ;
struct mp_log {int dummy; } ;
typedef  int /*<<< orphan*/  ASS_Library ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/ * ass_library_init () ; 
 int /*<<< orphan*/  ass_set_fonts_dir (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ass_set_message_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mp_log*) ; 
 int /*<<< orphan*/  message_callback ; 
 char* mp_find_config_file (int /*<<< orphan*/ *,struct mpv_global*,char*) ; 
 int /*<<< orphan*/  talloc_free (char*) ; 

ASS_Library *mp_ass_init(struct mpv_global *global, struct mp_log *log)
{
    char *path = mp_find_config_file(NULL, global, "fonts");
    ASS_Library *priv = ass_library_init();
    if (!priv)
        abort();
    ass_set_message_cb(priv, message_callback, log);
    if (path)
        ass_set_fonts_dir(priv, path);
    talloc_free(path);
    return priv;
}