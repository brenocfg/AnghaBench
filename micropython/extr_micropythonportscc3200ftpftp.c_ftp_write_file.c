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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  ftp_result_t ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_2__ {int /*<<< orphan*/  fp; } ;
typedef  scalar_t__ FRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_FTP_RESULT_FAILED ; 
 int /*<<< orphan*/  E_FTP_RESULT_OK ; 
 scalar_t__ FR_OK ; 
 scalar_t__ f_write (int /*<<< orphan*/ *,char*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ftp_close_files () ; 
 TYPE_1__ ftp_data ; 

__attribute__((used)) static ftp_result_t ftp_write_file (char *filebuf, uint32_t size) {
    ftp_result_t result = E_FTP_RESULT_FAILED;
    uint32_t actualsize;
    FRESULT res = f_write(&ftp_data.fp, filebuf, size, (UINT *)&actualsize);
    if ((actualsize == size) && (FR_OK == res)) {
        result = E_FTP_RESULT_OK;
    }
    else {
        ftp_close_files();
    }
    return result;
}