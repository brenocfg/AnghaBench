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
typedef  int /*<<< orphan*/  sample ;
typedef  int /*<<< orphan*/  BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  buffer_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buffer_strlen (int /*<<< orphan*/ *) ; 
 char* buffer_tostring (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  info (char*,int /*<<< orphan*/ ,char const*,char*) ; 
 int /*<<< orphan*/  isprint (char) ; 
 scalar_t__ unlikely (int) ; 

int discard_response(BUFFER *b, const char *backend) {
    char sample[1024];
    const char *s = buffer_tostring(b);
    char *d = sample, *e = &sample[sizeof(sample) - 1];

    for(; *s && d < e ;s++) {
        char c = *s;
        if(unlikely(!isprint(c))) c = ' ';
        *d++ = c;
    }
    *d = '\0';

    info("BACKEND: received %zu bytes from %s backend. Ignoring them. Sample: '%s'", buffer_strlen(b), backend, sample);
    buffer_flush(b);
    return 0;
}