#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  char_u ;
struct TYPE_4__ {int /*<<< orphan*/  uc; } ;
typedef  TYPE_1__ block8 ;
typedef  int UINT32_T ;
struct TYPE_5__ {int keysum; int /*<<< orphan*/  badcryptxt; int /*<<< orphan*/  cryptxt; int /*<<< orphan*/  plaintxt; int /*<<< orphan*/  salt; scalar_t__ password; } ;

/* Variables and functions */
 int ARRAY_LENGTH (TYPE_2__*) ; 
 int /*<<< orphan*/  EMSG (int /*<<< orphan*/ ) ; 
 int FAIL ; 
 int OK ; 
 scalar_t__ STRLEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  bf_check_tables (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bf_e_cblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bf_key_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* bf_test_data ; 
 int /*<<< orphan*/  ipa ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pax ; 
 int /*<<< orphan*/  sbi ; 
 int /*<<< orphan*/  sbx ; 

__attribute__((used)) static int
bf_self_test()
{
    int    i, bn;
    int    err = 0;
    block8 bk;
    UINT32_T ui = 0xffffffffUL;

    /* We can't simply use sizeof(UINT32_T), it would generate a compiler
     * warning. */
    if (ui != 0xffffffffUL || ui + 1 != 0) {
	err++;
	EMSG(_("E820: sizeof(uint32_t) != 4"));
    }

    if (!bf_check_tables(ipa, sbi, 0x6ffa520a))
	err++;

    bn = ARRAY_LENGTH(bf_test_data);
    for (i = 0; i < bn; i++)
    {
	bf_key_init((char_u *)(bf_test_data[i].password),
		    bf_test_data[i].salt,
		    (int)STRLEN(bf_test_data[i].salt));
	if (!bf_check_tables(pax, sbx, bf_test_data[i].keysum))
	    err++;

	/* Don't modify bf_test_data[i].plaintxt, self test is idempotent. */
	memcpy(bk.uc, bf_test_data[i].plaintxt, 8);
	bf_e_cblock(bk.uc);
	if (memcmp(bk.uc, bf_test_data[i].cryptxt, 8) != 0)
	{
	    if (err == 0 && memcmp(bk.uc, bf_test_data[i].badcryptxt, 8) == 0)
		EMSG(_("E817: Blowfish big/little endian use wrong"));
	    err++;
	}
    }

    return err > 0 ? FAIL : OK;
}