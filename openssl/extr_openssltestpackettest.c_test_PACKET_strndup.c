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
typedef  int /*<<< orphan*/  PACKET ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 int /*<<< orphan*/  PACKET_buf_init (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  PACKET_strndup (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  TEST_size_t_eq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_str_eq (char*,char*) ; 
 int /*<<< orphan*/  TEST_strn_eq (char*,char*,int) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static int test_PACKET_strndup(void)
{
    char buf1[10], buf2[10];
    char *data = NULL;
    PACKET pkt;
    int result = 0;

    memset(buf1, 'x', 10);
    memset(buf2, 'y', 10);
    buf2[5] = '\0';

    if (!TEST_true(PACKET_buf_init(&pkt, (unsigned char*)buf1, 10))
            || !TEST_true(PACKET_strndup(&pkt, &data))
            || !TEST_size_t_eq(strlen(data), 10)
            || !TEST_strn_eq(data, buf1, 10)
            || !TEST_true(PACKET_buf_init(&pkt, (unsigned char*)buf2, 10))
            || !TEST_true(PACKET_strndup(&pkt, &data))
            || !TEST_size_t_eq(strlen(data), 5)
            || !TEST_str_eq(data, buf2))
        goto end;

    result = 1;
end:
    OPENSSL_free(data);
    return result;
}