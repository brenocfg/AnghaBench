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
typedef  int /*<<< orphan*/  str ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_3__ {int length; char* data; int max; } ;
typedef  TYPE_1__ BUF_MEM ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_FLAGS_MEM_RDONLY ; 
 int /*<<< orphan*/  BIO_NOCLOSE ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_read (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  BIO_s_mem () ; 
 int /*<<< orphan*/  BIO_set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_set_mem_buf (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_mem_eq (char*,int,char const*,int) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_bio_memleak(void)
{
    int ok = 0;
    BIO *bio;
    BUF_MEM bufmem;
    static const char str[] = "BIO test\n";
    char buf[100];

    bio = BIO_new(BIO_s_mem());
    if (!TEST_ptr(bio))
        goto finish;
    bufmem.length = sizeof(str);
    bufmem.data = (char *) str;
    bufmem.max = bufmem.length;
    BIO_set_mem_buf(bio, &bufmem, BIO_NOCLOSE);
    BIO_set_flags(bio, BIO_FLAGS_MEM_RDONLY);
    if (!TEST_int_eq(BIO_read(bio, buf, sizeof(buf)), sizeof(str)))
        goto finish;
    if (!TEST_mem_eq(buf, sizeof(str), str, sizeof(str)))
        goto finish;
    ok = 1;

finish:
    BIO_free(bio);
    return ok;
}