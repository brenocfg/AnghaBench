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
typedef  int /*<<< orphan*/  mp_uint_t ;
typedef  int /*<<< orphan*/  mp_lexer_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ENOENT ; 
 scalar_t__ MZ_OK ; 
 scalar_t__ memzip_locate (char const*,void**,size_t*) ; 
 int /*<<< orphan*/ * mp_lexer_new_from_str_len (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_raise_OSError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qstr_from_str (char const*) ; 

mp_lexer_t *mp_lexer_new_from_file(const char *filename)
{
    void *data;
    size_t len;

    if (memzip_locate(filename, &data, &len) != MZ_OK) {
        mp_raise_OSError(MP_ENOENT);
    }

    return mp_lexer_new_from_str_len(qstr_from_str(filename), (const char *)data, (mp_uint_t)len, 0);
}