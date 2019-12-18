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
 char* mymalloc (int) ; 

char *
CGI_encode_entity(const char *in) {
    char *out, *p;
    int i, k;

    if (in == 0) {
        return 0;
    }
    for (i = k = 0; in[i] != 0; i++) {
        switch(in[i]) {

        case '<':
        case '>':
            k += 4;
            break;
        case '&':
        case '\'':
        case '\r':
        case '\n':
            k += 5;
            break;
        case '"':
            k += 6;
            break;
        default:
            k++;
            break;
        }
    }
    out = p = mymalloc(k + 1);

    for (i = 0; in[i] != 0; i++) {
        switch(in[i]) {

        case '<':
            *p++ = '&';
            *p++ = 'l';
            *p++ = 't';
            *p++ = ';';
            break;
        case '>':
            *p++ = '&';
            *p++ = 'g';
            *p++ = 't';
            *p++ = ';';
            break;
        case '&':
            *p++ = '&';
            *p++ = 'a';
            *p++ = 'm';
            *p++ = 'p';
            *p++ = ';';
            break;
        case '\'':
            *p++ = '&';
            *p++ = '#';
            *p++ = '3';
            *p++ = '9';
            *p++ = ';';
            break;
        case '\r':
            *p++ = '&';
            *p++ = '#';
            *p++ = '1';
            *p++ = '3';
            *p++ = ';';
            break;
        case '\n':
            *p++ = '&';
            *p++ = '#';
            *p++ = '1';
            *p++ = '0';
            *p++ = ';';
            break;
        case '"':
            *p++ = '&';
            *p++ = 'q';
            *p++ = 'u';
            *p++ = 'o';
            *p++ = 't';
            *p++ = ';';
            break;
        default:
            *p++ = in[i];
            break;
        }
    }
    *p = 0;
    return out;
}