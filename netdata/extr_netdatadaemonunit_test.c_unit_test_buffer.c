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
typedef  int /*<<< orphan*/  BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/ * buffer_create (int) ; 
 int /*<<< orphan*/  buffer_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buffer_sprintf (int /*<<< orphan*/ *,char const*,char*,char*,char*,char*) ; 
 scalar_t__ buffer_strlen (int /*<<< orphan*/ *) ; 
 char* buffer_tostring (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  snprintfz (char*,int,char const*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strlen (char*) ; 

int unit_test_buffer() {
    BUFFER *wb = buffer_create(1);
    char string[2048 + 1];
    char final[9000 + 1];
    int i;

    for(i = 0; i < 2048; i++)
        string[i] = (char)((i % 24) + 'a');
    string[2048] = '\0';

    const char *fmt = "string1: %s\nstring2: %s\nstring3: %s\nstring4: %s";
    buffer_sprintf(wb, fmt, string, string, string, string);
    snprintfz(final, 9000, fmt, string, string, string, string);

    const char *s = buffer_tostring(wb);

    if(buffer_strlen(wb) != strlen(final) || strcmp(s, final) != 0) {
        fprintf(stderr, "\nbuffer_sprintf() is faulty.\n");
        fprintf(stderr, "\nstring  : %s (length %zu)\n", string, strlen(string));
        fprintf(stderr, "\nbuffer  : %s (length %zu)\n", s, buffer_strlen(wb));
        fprintf(stderr, "\nexpected: %s (length %zu)\n", final, strlen(final));
        buffer_free(wb);
        return -1;
    }

    fprintf(stderr, "buffer_sprintf() works as expected.\n");
    buffer_free(wb);
    return 0;
}