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
typedef  int /*<<< orphan*/  tmpbuf ;
struct TYPE_3__ {int /*<<< orphan*/ * key; int /*<<< orphan*/  curr; int /*<<< orphan*/  fp; } ;
typedef  TYPE_1__ STANZA ;

/* Variables and functions */
 scalar_t__ BIO_gets (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_puts (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  BIO_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_s_mem () ; 
 int /*<<< orphan*/  TEST_error (char*) ; 
 int /*<<< orphan*/  TEST_int_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int read_key(STANZA *s)
{
    char tmpbuf[128];

    if (s->key == NULL) {
        if (!TEST_ptr(s->key = BIO_new(BIO_s_mem())))
            return 0;
    } else if (!TEST_int_gt(BIO_reset(s->key), 0)) {
        return 0;
    }

    /* Read to PEM end line and place content in memory BIO */
    while (BIO_gets(s->fp, tmpbuf, sizeof(tmpbuf))) {
        s->curr++;
        if (!TEST_int_gt(BIO_puts(s->key, tmpbuf), 0))
            return 0;
        if (strncmp(tmpbuf, "-----END", 8) == 0)
            return 1;
    }
    TEST_error("Can't find key end");
    return 0;
}