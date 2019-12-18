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
struct TYPE_2__ {int /*<<< orphan*/  state; scalar_t__ enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_FTP_STE_START ; 
 TYPE_1__ ftp_data ; 

__attribute__((used)) static void ftp_wait_for_enabled (void) {
    // Check if the telnet service has been enabled
    if (ftp_data.enabled) {
        ftp_data.state = E_FTP_STE_START;
    }
}