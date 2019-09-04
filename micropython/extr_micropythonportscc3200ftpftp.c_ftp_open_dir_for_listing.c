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
typedef  int /*<<< orphan*/  ftp_result_t ;
struct TYPE_2__ {int listroot; int /*<<< orphan*/  e_open; int /*<<< orphan*/  dp; } ;
typedef  scalar_t__ FRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_FTP_DIR_OPEN ; 
 int /*<<< orphan*/  E_FTP_RESULT_CONTINUE ; 
 int /*<<< orphan*/  E_FTP_RESULT_FAILED ; 
 scalar_t__ FR_OK ; 
 scalar_t__ f_opendir_helper (int /*<<< orphan*/ *,char const*) ; 
 TYPE_1__ ftp_data ; 

__attribute__((used)) static ftp_result_t ftp_open_dir_for_listing (const char *path) {
    // "hack" to detect the root directory
    if (path[0] == '/' && path[1] == '\0') {
        ftp_data.listroot = true;
    } else {
        FRESULT res;
        res = f_opendir_helper(&ftp_data.dp, path); /* Open the directory */
        if (res != FR_OK) {
            return E_FTP_RESULT_FAILED;
        }
        ftp_data.e_open = E_FTP_DIR_OPEN;
        ftp_data.listroot = false;
    }
    return E_FTP_RESULT_CONTINUE;
}