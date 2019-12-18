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
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t const) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int join(char buf[], size_t buf_size, const char *name,
                const char *tail, const char *desc)
{
    const size_t name_len = strlen(name), tail_len = strlen(tail);

    if (name_len + tail_len + 1 > buf_size) {
        BIO_printf(bio_err, "%s '%s' too long\n", desc, name);
        return 0;
    }
    memcpy(buf, name, name_len);
    memcpy(buf + name_len, tail, tail_len + 1);
    return 1;
}