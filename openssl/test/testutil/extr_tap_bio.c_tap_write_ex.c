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
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/ * BIO_get_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_set_data (int /*<<< orphan*/ *,char*) ; 
 int subtest_level () ; 
 int /*<<< orphan*/  write_string (int /*<<< orphan*/ *,char const*,int) ; 

__attribute__((used)) static int tap_write_ex(BIO *b, const char *buf, size_t size, size_t *in_size)
{
    static char empty[] = "";
    BIO *next = BIO_next(b);
    size_t i;
    int j;

    for (i = 0; i < size; i++) {
        if (BIO_get_data(b) == NULL) {
            BIO_set_data(b, empty);
            for (j = 0; j < subtest_level(); j++)
                if (!write_string(next, " ", 1))
                    goto err;
            if (!write_string(next, "# ", 2))
                goto err;
        }
        if (!write_string(next, buf + i, 1))
            goto err;
        if (buf[i] == '\n')
            BIO_set_data(b, NULL);
    }
    *in_size = i;
    return 1;

err:
    *in_size = i;
    return 0;
}