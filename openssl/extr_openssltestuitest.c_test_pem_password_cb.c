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

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_strlcpy (char*,char*,size_t) ; 
 int strlen (char*) ; 

__attribute__((used)) static int test_pem_password_cb(char *buf, int size, int rwflag, void *userdata)
{
    OPENSSL_strlcpy(buf, (char *)userdata, (size_t)size);
    return strlen(buf);
}