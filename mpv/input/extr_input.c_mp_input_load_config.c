#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct input_ctx {TYPE_1__* opts; int /*<<< orphan*/  global; } ;
struct TYPE_11__ {scalar_t__ len; } ;
typedef  TYPE_2__ bstr ;
struct TYPE_10__ {char* config_file; scalar_t__ use_gamepad; } ;

/* Variables and functions */
 TYPE_2__ bstr0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bstr_eatstart0 (TYPE_2__*,char*) ; 
 TYPE_2__ bstr_getline (TYPE_2__,TYPE_2__*) ; 
 int /*<<< orphan*/  bstr_startswith0 (TYPE_2__,char*) ; 
 int /*<<< orphan*/  builtin_input_conf ; 
 int /*<<< orphan*/  input_lock (struct input_ctx*) ; 
 int /*<<< orphan*/  input_unlock (struct input_ctx*) ; 
 int /*<<< orphan*/  m_option_type_string ; 
 char** mp_find_all_config_files (void*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mp_input_pipe_add (struct input_ctx*,char*) ; 
 int /*<<< orphan*/  mp_input_sdl_gamepad_add (struct input_ctx*) ; 
 int /*<<< orphan*/  mp_read_option_raw (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  parse_config (struct input_ctx*,int,TYPE_2__,char*,int /*<<< orphan*/ *) ; 
 int parse_config_file (struct input_ctx*,char*,int) ; 
 int /*<<< orphan*/  reload_opts (struct input_ctx*,int) ; 
 int /*<<< orphan*/  talloc_free (char*) ; 
 void* talloc_new (int /*<<< orphan*/ *) ; 

void mp_input_load_config(struct input_ctx *ictx)
{
    input_lock(ictx);

    reload_opts(ictx, false);

    // "Uncomment" the default key bindings in etc/input.conf and add them.
    // All lines that do not start with '# ' are parsed.
    bstr builtin = bstr0(builtin_input_conf);
    while (builtin.len) {
        bstr line = bstr_getline(builtin, &builtin);
        bstr_eatstart0(&line, "#");
        if (!bstr_startswith0(line, " "))
            parse_config(ictx, true, line, "<builtin>", NULL);
    }

    bool config_ok = false;
    if (ictx->opts->config_file && ictx->opts->config_file[0])
        config_ok = parse_config_file(ictx, ictx->opts->config_file, true);
    if (!config_ok) {
        // Try global conf dir
        void *tmp = talloc_new(NULL);
        char **files = mp_find_all_config_files(tmp, ictx->global, "input.conf");
        for (int n = 0; files && files[n]; n++)
            parse_config_file(ictx, files[n], false);
        talloc_free(tmp);
    }

#if HAVE_WIN32_PIPES
    char *ifile;
    mp_read_option_raw(ictx->global, "input-file", &m_option_type_string, &ifile);
    if (ifile && ifile[0])
        mp_input_pipe_add(ictx, ifile);
    talloc_free(ifile);
#endif

#if HAVE_SDL2_GAMEPAD
    if (ictx->opts->use_gamepad) {
        mp_input_sdl_gamepad_add(ictx);
    }
#endif

    input_unlock(ictx);
}