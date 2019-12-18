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
 int /*<<< orphan*/  OPENSSL_strlcat (char*,char const*,size_t) ; 
 int /*<<< orphan*/  OPENSSL_strlcpy (char*,char const*,size_t) ; 
 char* OPENSSL_zalloc (size_t) ; 
 int strlen (char const*) ; 

char *test_mk_file_path(const char *dir, const char *file)
{
# ifndef OPENSSL_SYS_VMS
    const char *sep = "/";
# else
    const char *sep = "";
# endif
    size_t len = strlen(dir) + strlen(sep) + strlen(file) + 1;
    char *full_file = OPENSSL_zalloc(len);

    if (full_file != NULL) {
        OPENSSL_strlcpy(full_file, dir, len);
        OPENSSL_strlcat(full_file, sep, len);
        OPENSSL_strlcat(full_file, file, len);
    }

    return full_file;
}