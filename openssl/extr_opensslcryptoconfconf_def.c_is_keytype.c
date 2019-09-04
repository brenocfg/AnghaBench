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
struct TYPE_3__ {scalar_t__ meth_data; } ;
typedef  TYPE_1__ CONF ;

/* Variables and functions */

__attribute__((used)) static int is_keytype(const CONF *conf, char c, unsigned short type)
{
    const unsigned short * keytypes = (const unsigned short *) conf->meth_data;
    unsigned char key = (unsigned char)c;

#ifdef CHARSET_EBCDIC
# if CHAR_BIT > 8
    if (key > 255) {
        /* key is out of range for os_toascii table */
        return 0;
    }
# endif
    /* convert key from ebcdic to ascii */
    key = os_toascii[key];
#endif

    if (key > 127) {
        /* key is not a seven bit ascii character */
        return 0;
    }

    return (keytypes[key] & type) ? 1 : 0;
}