#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ e_open; int /*<<< orphan*/  dp; int /*<<< orphan*/  fp; } ;

/* Variables and functions */
 scalar_t__ E_FTP_DIR_OPEN ; 
 scalar_t__ E_FTP_FILE_OPEN ; 
 scalar_t__ E_FTP_NOTHING_OPEN ; 
 int /*<<< orphan*/  f_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  f_closedir (int /*<<< orphan*/ *) ; 
 TYPE_1__ ftp_data ; 

__attribute__((used)) static void ftp_close_files (void) {
    if (ftp_data.e_open == E_FTP_FILE_OPEN) {
        f_close(&ftp_data.fp);
    }
    else if (ftp_data.e_open == E_FTP_DIR_OPEN) {
        f_closedir(&ftp_data.dp);
    }
    ftp_data.e_open = E_FTP_NOTHING_OPEN;
}