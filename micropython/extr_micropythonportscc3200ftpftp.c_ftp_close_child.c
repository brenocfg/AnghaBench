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
typedef  size_t uint ;

/* Variables and functions */
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static void ftp_close_child (char *pwd) {
    uint len = strlen(pwd);
    while (len && (pwd[len] != '/')) {
        len--;
    }
    if (len == 0) {
        strcpy (pwd, "/");
    } else {
        pwd[len] = '\0';
    }
}