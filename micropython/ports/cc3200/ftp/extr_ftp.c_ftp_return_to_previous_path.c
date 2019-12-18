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
typedef  int uint ;

/* Variables and functions */
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void ftp_return_to_previous_path (char *pwd, char *dir) {
    uint newlen = strlen(pwd) - strlen(dir);
    if ((newlen > 2) && (pwd[newlen - 1] == '/')) {
        pwd[newlen - 1] = '\0';
    }
    else {
        if (newlen == 0) {
            strcpy (pwd, "/");
        } else {
            pwd[newlen] = '\0';
        }
    }
}