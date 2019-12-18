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
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* app_malloc (size_t,char*) ; 
 size_t strlen (char const*) ; 

unsigned char *next_protos_parse(size_t *outlen, const char *in)
{
    size_t len;
    unsigned char *out;
    size_t i, start = 0;
    size_t skipped = 0;

    len = strlen(in);
    if (len == 0 || len >= 65535)
        return NULL;

    out = app_malloc(len + 1, "NPN buffer");
    for (i = 0; i <= len; ++i) {
        if (i == len || in[i] == ',') {
            /*
             * Zero-length ALPN elements are invalid on the wire, we could be
             * strict and reject the entire string, but just ignoring extra
             * commas seems harmless and more friendly.
             *
             * Every comma we skip in this way puts the input buffer another
             * byte ahead of the output buffer, so all stores into the output
             * buffer need to be decremented by the number commas skipped.
             */
            if (i == start) {
                ++start;
                ++skipped;
                continue;
            }
            if (i - start > 255) {
                OPENSSL_free(out);
                return NULL;
            }
            out[start-skipped] = (unsigned char)(i - start);
            start = i + 1;
        } else {
            out[i + 1 - skipped] = in[i];
        }
    }

    if (len <= skipped) {
        OPENSSL_free(out);
        return NULL;
    }

    *outlen = len + 1 - skipped;
    return out;
}