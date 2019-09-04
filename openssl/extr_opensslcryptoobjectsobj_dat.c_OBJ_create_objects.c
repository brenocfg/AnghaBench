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
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int BIO_gets (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  OBJ_create (char*,char*,char*) ; 
 int /*<<< orphan*/  ossl_isalnum (char) ; 
 scalar_t__ ossl_isdigit (char) ; 
 scalar_t__ ossl_isspace (char) ; 

int OBJ_create_objects(BIO *in)
{
    char buf[512];
    int i, num = 0;
    char *o, *s, *l = NULL;

    for (;;) {
        s = o = NULL;
        i = BIO_gets(in, buf, 512);
        if (i <= 0)
            return num;
        buf[i - 1] = '\0';
        if (!ossl_isalnum(buf[0]))
            return num;
        o = s = buf;
        while (ossl_isdigit(*s) || *s == '.')
            s++;
        if (*s != '\0') {
            *(s++) = '\0';
            while (ossl_isspace(*s))
                s++;
            if (*s == '\0') {
                s = NULL;
            } else {
                l = s;
                while (*l != '\0' && !ossl_isspace(*l))
                    l++;
                if (*l != '\0') {
                    *(l++) = '\0';
                    while (ossl_isspace(*l))
                        l++;
                    if (*l == '\0') {
                        l = NULL;
                    }
                } else {
                    l = NULL;
                }
            }
        } else {
            s = NULL;
        }
        if (*o == '\0')
            return num;
        if (!OBJ_create(o, s, l))
            return num;
        num++;
    }
}