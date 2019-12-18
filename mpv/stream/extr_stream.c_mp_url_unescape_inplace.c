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
 int hex2dec (char) ; 
 int strlen (char*) ; 

void mp_url_unescape_inplace(char *url)
{
    for (int len = strlen(url), i = 0, o = 0; i <= len;) {
        if ((url[i] != '%') || (i > len - 3)) {  // %NN can't start after len-3
            url[o++] = url[i++];
            continue;
        }

        int msd = hex2dec(url[i + 1]),
            lsd = hex2dec(url[i + 2]);

        if (msd >= 0 && lsd >= 0) {
            url[o++] = 16 * msd + lsd;
            i += 3;
        } else {
            url[o++] = url[i++];
            url[o++] = url[i++];
            url[o++] = url[i++];
        }
    }
}