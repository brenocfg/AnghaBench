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
typedef  int /*<<< orphan*/  wchar_t ;

/* Variables and functions */
 int /*<<< orphan*/ ** CommandLineToArgvW (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  GetCommandLineW () ; 
 int /*<<< orphan*/  MP_TARRAY_APPEND (int /*<<< orphan*/ *,char**,int,char*) ; 
 int /*<<< orphan*/  has_redirected_stdio () ; 
 int /*<<< orphan*/  microsoft_nonsense () ; 
 char* mp_to_utf8 (char**,int /*<<< orphan*/ *) ; 
 int mpv_main (int,char**) ; 
 int /*<<< orphan*/  talloc_free (char**) ; 
 int terminal_try_attach () ; 

int main(int argc_, char **argv_)
{
    microsoft_nonsense();

    // If started from the console wrapper (see osdep/win32-console-wrapper.c),
    // attach to the console and set up the standard IO handles
    bool has_console = terminal_try_attach();

    // If mpv is started from Explorer, the Run dialog or the Start Menu, it
    // will have no console and no standard IO handles. In this case, the user
    // is expecting mpv to show some UI, so enable the pseudo-GUI profile.
    bool gui = !has_console && !has_redirected_stdio();

    int argc = 0;
    wchar_t **argv = CommandLineToArgvW(GetCommandLineW(), &argc);

    int argv_len = 0;
    char **argv_u8 = NULL;

    // Build mpv's UTF-8 argv, and add the pseudo-GUI profile if necessary
    if (argc > 0 && argv[0])
        MP_TARRAY_APPEND(NULL, argv_u8, argv_len, mp_to_utf8(argv_u8, argv[0]));
    if (gui) {
        MP_TARRAY_APPEND(NULL, argv_u8, argv_len,
                         "--player-operation-mode=pseudo-gui");
    }
    for (int i = 1; i < argc; i++)
        MP_TARRAY_APPEND(NULL, argv_u8, argv_len, mp_to_utf8(argv_u8, argv[i]));
    MP_TARRAY_APPEND(NULL, argv_u8, argv_len, NULL);

    int ret = mpv_main(argv_len - 1, argv_u8);

    talloc_free(argv_u8);
    return ret;
}