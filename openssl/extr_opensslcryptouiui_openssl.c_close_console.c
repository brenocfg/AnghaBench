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
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (scalar_t__) ; 
 scalar_t__ stderr ; 
 scalar_t__ stdin ; 
 scalar_t__ tty_in ; 
 scalar_t__ tty_out ; 

__attribute__((used)) static int close_console(UI *ui)
{
    if (tty_in != stdin)
        fclose(tty_in);
    if (tty_out != stderr)
        fclose(tty_out);
# ifdef OPENSSL_SYS_VMS
    status = sys$dassgn(channel);
    if (status != SS$_NORMAL) {
        char tmp_num[12];

        BIO_snprintf(tmp_num, sizeof(tmp_num) - 1, "%%X%08X", status);
        UIerr(UI_F_CLOSE_CONSOLE, UI_R_SYSDASSGN_ERROR);
        ERR_add_error_data(2, "status=", tmp_num);
        return 0;
    }
# endif
    CRYPTO_THREAD_unlock(ui->lock);

    return 1;
}