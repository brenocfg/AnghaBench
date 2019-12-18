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
typedef  int /*<<< orphan*/  strbuf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  fputc (char const,int /*<<< orphan*/ *) ; 
 int getc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * savechar (int /*<<< orphan*/ *,int,char const) ; 

__attribute__((used)) static strbuf *
copyvalue(const char *boundary, FILE *in, const int wantfile,
    strbuf *value, FILE *out)
{
    int c, i, k, matched;

    matched = k = 0;

    while ((c = getc(in)) != EOF) {

        /*
         * If we partially match the boundary, then we copy the
         * entire matching prefix to the output.  We do not need to
         * backtrack and look for shorter matching prefixes because
         * they cannot exist.  The boundary always begins with '\r'
         * and never contains another '\r'.
         */

        if (matched > 0 && c != boundary[matched]) {
            for (i = 0; i < matched; i++) {
                if (wantfile == 0) {
                    value = savechar(value, k++, boundary[i]);
                }
                else if (out != 0) {
                    fputc(boundary[i], out);
                }
            }
            matched = 0;
        }

        /* check for full or partial boundary match */

        if (c == boundary[matched]) {
            if (boundary[++matched] == 0) {
                break;   /* full match */
            }
            continue;    /* partial match */
        }

        /* no match, so copy byte to output */

        if (wantfile == 0) {
            value = savechar(value, k++, c);
        }
        else if (out != 0) {
            fputc(c, out);
        }
    }
    if (wantfile == 0) {
        return savechar(value, k, 0);
    }
    return 0;
}