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
 int BIO_snprintf (char*,int,char*,...) ; 
 size_t PEM_BUFSIZE ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

void PEM_dek_info(char *buf, const char *type, int len, char *str)
{
    long i;
    char *p = buf + strlen(buf);
    int j = PEM_BUFSIZE - (size_t)(p - buf), n;

    n = BIO_snprintf(p, j, "DEK-Info: %s,", type);
    if (n > 0) {
        j -= n;
        p += n;
        for (i = 0; i < len; i++) {
            n = BIO_snprintf(p, j, "%02X", 0xff & str[i]);
            if (n <= 0)
                return;
            j -= n;
            p += n;
        }
        if (j > 1)
            strcpy(p, "\n");
    }
}