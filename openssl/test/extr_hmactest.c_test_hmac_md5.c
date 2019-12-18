#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  digest; int /*<<< orphan*/  data_len; int /*<<< orphan*/  data; int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_md5 () ; 
 int /*<<< orphan*/  HMAC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5_DIGEST_LENGTH ; 
 int /*<<< orphan*/  TEST_str_eq (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ebcdic2ascii (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* pt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* test ; 

__attribute__((used)) static int test_hmac_md5(int idx)
{
    char *p;
#  ifdef CHARSET_EBCDIC
    ebcdic2ascii(test[0].data, test[0].data, test[0].data_len);
    ebcdic2ascii(test[1].data, test[1].data, test[1].data_len);
    ebcdic2ascii(test[2].key, test[2].key, test[2].key_len);
    ebcdic2ascii(test[2].data, test[2].data, test[2].data_len);
#  endif

    p = pt(HMAC(EVP_md5(),
                test[idx].key, test[idx].key_len,
                test[idx].data, test[idx].data_len, NULL, NULL),
                MD5_DIGEST_LENGTH);

    if (!TEST_str_eq(p, test[idx].digest))
      return 0;

    return 1;
}