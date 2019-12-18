#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int echo_format; } ;
typedef  TYPE_1__ nn_options_t ;

/* Variables and functions */
#define  NN_ECHO_ASCII 133 
#define  NN_ECHO_HEX 132 
#define  NN_ECHO_MSGPACK 131 
#define  NN_ECHO_QUOTED 130 
#define  NN_ECHO_RAW 129 
#define  NN_NO_ECHO 128 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwrite (char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isprint (char) ; 
 int /*<<< orphan*/  stdout ; 

void nn_print_message (nn_options_t *options, char *buf, int buflen)
{
    switch (options->echo_format) {
    case NN_NO_ECHO:
        return;
    case NN_ECHO_RAW:
        fwrite (buf, 1, buflen, stdout);
        break;
    case NN_ECHO_ASCII:
        for (; buflen > 0; --buflen, ++buf) {
            if (isprint (*buf)) {
                fputc (*buf, stdout);
            } else {
                fputc ('.', stdout);
            }
        }
        fputc ('\n', stdout);
        break;
    case NN_ECHO_QUOTED:
        fputc ('"', stdout);
        for (; buflen > 0; --buflen, ++buf) {
            switch (*buf) {
            case '\n':
                fprintf (stdout, "\\n");
                break;
            case '\r':
                fprintf (stdout, "\\r");
                break;
            case '\\':
            case '\"':
                fprintf (stdout, "\\%c", *buf);
                break;
            default:
                if (isprint (*buf)) {
                    fputc (*buf, stdout);
                } else {
                    fprintf (stdout, "\\x%02x", (unsigned char)*buf);
                }
            }
        }
        fprintf (stdout, "\"\n");
        break;
    case NN_ECHO_MSGPACK:
        if (buflen < 256) {
            fputc ('\xc4', stdout);
            fputc (buflen, stdout);
            fwrite (buf, 1, buflen, stdout);
        } else if (buflen < 65536) {
            fputc ('\xc5', stdout);
            fputc (buflen >> 8, stdout);
            fputc (buflen & 0xff, stdout);
            fwrite (buf, 1, buflen, stdout);
        } else {
            fputc ('\xc6', stdout);
            fputc (buflen >> 24, stdout);
            fputc ((buflen >> 16) & 0xff, stdout);
            fputc ((buflen >> 8) & 0xff, stdout);
            fputc (buflen & 0xff, stdout);
            fwrite (buf, 1, buflen, stdout);
        }
        break;
    case NN_ECHO_HEX:
        fputc ('"', stdout);
        for (; buflen > 0; --buflen, ++buf) {
             fprintf (stdout, "\\x%02x", (unsigned char)*buf);
        }
        fprintf (stdout, "\"\n");
        break;
    
    }
    fflush (stdout);
}