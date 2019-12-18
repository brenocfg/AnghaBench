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
struct TYPE_2__ {int special_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  ftp_close_files () ; 
 TYPE_1__ ftp_data ; 
 int /*<<< orphan*/  updater_finnish () ; 

__attribute__((used)) static void ftp_close_filesystem_on_error (void) {
    ftp_close_files();
    if (ftp_data.special_file) {
        updater_finnish ();
        ftp_data.special_file = false;
    }
}