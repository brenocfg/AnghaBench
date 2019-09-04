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
 int fread (char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char getc (int /*<<< orphan*/ ) ; 
 scalar_t__ isdigit (int) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  stdin ; 

__attribute__((used)) static char **
read_env(void) {
    char **env;
    char *buf, *p;
    int i, k, len;

    /* read length of environment data, eg, "175:" */

    for (len = 0; isdigit(k = getc(stdin)); ) {
        len = len * 10 + k - '0';
    }
    if (k != ':' || len < 4) {
        return 0;
    }

    /* read the environment strings */

    buf = (char *) malloc(len);
    if (fread(buf, 1, len, stdin) != len || getc(stdin) != ',') {
        free(buf);
        return 0;
    }

    /* replace null between each name and value with '=' */

    for (i = k = 0; i < len; i++) {
        if (buf[i] == 0 && (++k & 1)) {
            buf[i] = '=';
        }
    }

    /* build environment array */

    k = k / 2 + 1;
    env = (char **) malloc(k * sizeof(*env));
    p = buf;
    for (i = k = 0; i < len; i++) {
        if (buf[i] == 0) {
            env[k++] = p;
            p = buf + i + 1;
        }
    }
    env[k] = 0;
    return env;
}