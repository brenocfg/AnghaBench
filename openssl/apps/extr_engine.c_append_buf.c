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
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 char* OPENSSL_realloc (char*,int) ; 
 char* app_malloc (int,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int append_buf(char **buf, int *size, const char *s)
{
    const int expand = 256;
    int len = strlen(s) + 1;
    char *p = *buf;

    if (p == NULL) {
        *size = ((len + expand - 1) / expand) * expand;
        p = *buf = app_malloc(*size, "engine buffer");
    } else {
        const int blen = strlen(p);

        if (blen > 0)
            len += 2 + blen;

        if (len > *size) {
            *size = ((len + expand - 1) / expand) * expand;
            p = OPENSSL_realloc(p, *size);
            if (p == NULL) {
                OPENSSL_free(*buf);
                *buf = NULL;
                return 0;
            }
            *buf = p;
        }

        if (blen > 0) {
            p += blen;
            *p++ = ',';
            *p++ = ' ';
        }
    }

    strcpy(p, s);
    return 1;
}