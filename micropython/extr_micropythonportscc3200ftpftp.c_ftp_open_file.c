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
struct TYPE_2__ {int /*<<< orphan*/  e_open; int /*<<< orphan*/  fp; } ;
typedef  scalar_t__ FRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_FTP_FILE_OPEN ; 
 scalar_t__ FR_OK ; 
 scalar_t__ f_open_helper (int /*<<< orphan*/ *,char const*,int) ; 
 TYPE_1__ ftp_data ; 

__attribute__((used)) static bool ftp_open_file (const char *path, int mode) {
    FRESULT res = f_open_helper(&ftp_data.fp, path, mode);
    if (res != FR_OK) {
        return false;
    }
    ftp_data.e_open = E_FTP_FILE_OPEN;
    return true;
}