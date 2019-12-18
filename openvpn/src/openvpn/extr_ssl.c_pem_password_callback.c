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
struct TYPE_3__ {int /*<<< orphan*/  password; } ;

/* Variables and functions */
 TYPE_1__ passbuf ; 
 int /*<<< orphan*/  pem_password_setup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  purge_user_pass (TYPE_1__*,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpynt (char*,int /*<<< orphan*/ ,int) ; 

int
pem_password_callback(char *buf, int size, int rwflag, void *u)
{
    if (buf)
    {
        /* prompt for password even if --askpass wasn't specified */
        pem_password_setup(NULL);
        strncpynt(buf, passbuf.password, size);
        purge_user_pass(&passbuf, false);

        return strlen(buf);
    }
    return 0;
}