#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ UI ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_write_lock (int /*<<< orphan*/ ) ; 
 void* fopen (char*,char*) ; 
 int is_a_tty ; 
 int /*<<< orphan*/ * stderr ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/ * tty_in ; 
 int /*<<< orphan*/ * tty_out ; 

__attribute__((used)) static int open_console(UI *ui)
{
    CRYPTO_THREAD_write_lock(ui->lock);
    is_a_tty = 1;

# if defined(OPENSSL_SYS_VXWORKS)
    tty_in = stdin;
    tty_out = stderr;
# elif defined(_WIN32) && !defined(_WIN32_WCE)
    if ((tty_out = fopen("conout$", "w")) == NULL)
        tty_out = stderr;

    if (GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &tty_orig)) {
        tty_in = stdin;
    } else {
        is_a_tty = 0;
        if ((tty_in = fopen("conin$", "r")) == NULL)
            tty_in = stdin;
    }
# else
#  ifdef OPENSSL_SYS_MSDOS
#   define DEV_TTY "con"
#  else
#   define DEV_TTY "/dev/tty"
#  endif
    if ((tty_in = fopen(DEV_TTY, "r")) == NULL)
        tty_in = stdin;
    if ((tty_out = fopen(DEV_TTY, "w")) == NULL)
        tty_out = stderr;
# endif

# if defined(TTY_get) && !defined(OPENSSL_SYS_VMS)
    if (TTY_get(fileno(tty_in), &tty_orig) == -1) {
#  ifdef ENOTTY
        if (errno == ENOTTY)
            is_a_tty = 0;
        else
#  endif
#  ifdef EINVAL
            /*
             * Ariel Glenn reports that solaris can return EINVAL instead.
             * This should be ok
             */
        if (errno == EINVAL)
            is_a_tty = 0;
        else
#  endif
#  ifdef ENXIO
            /*
             * Solaris can return ENXIO.
             * This should be ok
             */
        if (errno == ENXIO)
            is_a_tty = 0;
        else
#  endif
#  ifdef EIO
            /*
             * Linux can return EIO.
             * This should be ok
             */
        if (errno == EIO)
            is_a_tty = 0;
        else
#  endif
#  ifdef ENODEV
            /*
             * MacOS X returns ENODEV (Operation not supported by device),
             * which seems appropriate.
             */
        if (errno == ENODEV)
            is_a_tty = 0;
        else
#  endif
            {
                char tmp_num[10];
                BIO_snprintf(tmp_num, sizeof(tmp_num) - 1, "%d", errno);
                UIerr(UI_F_OPEN_CONSOLE, UI_R_UNKNOWN_TTYGET_ERRNO_VALUE);
                ERR_add_error_data(2, "errno=", tmp_num);

                return 0;
            }
    }
# endif
# ifdef OPENSSL_SYS_VMS
    status = sys$assign(&terminal, &channel, 0, 0);

    /* if there isn't a TT device, something is very wrong */
    if (status != SS$_NORMAL) {
        char tmp_num[12];

        BIO_snprintf(tmp_num, sizeof(tmp_num) - 1, "%%X%08X", status);
        UIerr(UI_F_OPEN_CONSOLE, UI_R_SYSASSIGN_ERROR);
        ERR_add_error_data(2, "status=", tmp_num);
        return 0;
    }

    status = sys$qiow(0, channel, IO$_SENSEMODE, &iosb, 0, 0, tty_orig, 12,
                      0, 0, 0, 0);

    /* If IO$_SENSEMODE doesn't work, this is not a terminal device */
    if ((status != SS$_NORMAL) || (iosb.iosb$w_value != SS$_NORMAL))
        is_a_tty = 0;
# endif
    return 1;
}