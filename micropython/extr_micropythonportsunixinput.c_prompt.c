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

/* Variables and functions */
 char* fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 int strlen (char*) ; 

char *prompt(char *p) {
    // simple read string
    static char buf[256];
    fputs(p, stdout);
    char *s = fgets(buf, sizeof(buf), stdin);
    if (!s) {
        return NULL;
    }
    int l = strlen(buf);
    if (buf[l - 1] == '\n') {
        buf[l - 1] = 0;
    } else {
        l++;
    }
    char *line = malloc(l);
    memcpy(line, buf, l);
    return line;
}