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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_gets (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  TEST_error (char*) ; 
 int /*<<< orphan*/  _UC (char) ; 
 scalar_t__ isspace (int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 

__attribute__((used)) static char *read_to_eol(BIO *f)
{
    static char buf[1024];
    int n;

    if (!BIO_gets(f, buf, sizeof(buf)))
        return NULL;

    n = strlen(buf);
    if (buf[n - 1] != '\n') {
        if (n + 1 == sizeof(buf))
            TEST_error("input too long");
        else
            TEST_error("EOF before newline");
        return NULL;
    }

    /* Trim trailing whitespace */
    while (n > 0 && isspace(_UC(buf[n - 1])))
        buf[--n] = '\0';

    return buf;
}