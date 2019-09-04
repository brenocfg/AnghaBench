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
typedef  int /*<<< orphan*/  UI_STRING ;
typedef  int /*<<< orphan*/  UI ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  OPENSSL_cleanse (char*,int) ; 
 scalar_t__ SIGINT ; 
 scalar_t__ UI_set_result (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  echo_console (int /*<<< orphan*/ *) ; 
 scalar_t__ feof (int /*<<< orphan*/ ) ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 char* fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ intr_signal ; 
 int /*<<< orphan*/  noecho_console (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  popsig () ; 
 int /*<<< orphan*/  pushsig () ; 
 int /*<<< orphan*/  read_till_nl (int /*<<< orphan*/ ) ; 
 scalar_t__ strchr (char*,char) ; 
 int /*<<< orphan*/  tty_in ; 
 int /*<<< orphan*/  tty_out ; 

__attribute__((used)) static int read_string_inner(UI *ui, UI_STRING *uis, int echo, int strip_nl)
{
    static int ps;
    int ok;
    char result[BUFSIZ];
    int maxsize = BUFSIZ - 1;
# if !defined(OPENSSL_SYS_WINCE)
    char *p = NULL;
    int echo_eol = !echo;

    intr_signal = 0;
    ok = 0;
    ps = 0;

    pushsig();
    ps = 1;

    if (!echo && !noecho_console(ui))
        goto error;
    ps = 2;

    result[0] = '\0';
#  if defined(_WIN32)
    if (is_a_tty) {
        DWORD numread;
#   if defined(CP_UTF8)
        if (GetEnvironmentVariableW(L"OPENSSL_WIN32_UTF8", NULL, 0) != 0) {
            WCHAR wresult[BUFSIZ];

            if (ReadConsoleW(GetStdHandle(STD_INPUT_HANDLE),
                         wresult, maxsize, &numread, NULL)) {
                if (numread >= 2 &&
                    wresult[numread-2] == L'\r' &&
                    wresult[numread-1] == L'\n') {
                    wresult[numread-2] = L'\n';
                    numread--;
                }
                wresult[numread] = '\0';
                if (WideCharToMultiByte(CP_UTF8, 0, wresult, -1,
                                        result, sizeof(result), NULL, 0) > 0)
                    p = result;

                OPENSSL_cleanse(wresult, sizeof(wresult));
            }
        } else
#   endif
        if (ReadConsoleA(GetStdHandle(STD_INPUT_HANDLE),
                         result, maxsize, &numread, NULL)) {
            if (numread >= 2 &&
                result[numread-2] == '\r' && result[numread-1] == '\n') {
                result[numread-2] = '\n';
                numread--;
            }
            result[numread] = '\0';
            p = result;
        }
    } else
#  elif defined(OPENSSL_SYS_MSDOS)
    if (!echo) {
        noecho_fgets(result, maxsize, tty_in);
        p = result;             /* FIXME: noecho_fgets doesn't return errors */
    } else
#  endif
    p = fgets(result, maxsize, tty_in);
    if (p == NULL)
        goto error;
    if (feof(tty_in))
        goto error;
    if (ferror(tty_in))
        goto error;
    if ((p = (char *)strchr(result, '\n')) != NULL) {
        if (strip_nl)
            *p = '\0';
    } else if (!read_till_nl(tty_in))
        goto error;
    if (UI_set_result(ui, uis, result) >= 0)
        ok = 1;

 error:
    if (intr_signal == SIGINT)
        ok = -1;
    if (echo_eol)
        fprintf(tty_out, "\n");
    if (ps >= 2 && !echo && !echo_console(ui))
        ok = 0;

    if (ps >= 1)
        popsig();
# else
    ok = 1;
# endif

    OPENSSL_cleanse(result, BUFSIZ);
    return ok;
}