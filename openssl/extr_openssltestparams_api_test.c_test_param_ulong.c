#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  out ;
typedef  int /*<<< orphan*/  in ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_8__ {int len; unsigned long* value; } ;
struct TYPE_7__ {unsigned long* data; } ;
typedef  TYPE_1__ OSSL_PARAM ;

/* Variables and functions */
 int MAX_LEN ; 
 int /*<<< orphan*/  OSSL_PARAM_get_ulong (TYPE_1__*,unsigned long*) ; 
 int /*<<< orphan*/  OSSL_PARAM_set_ulong (TYPE_1__*,unsigned long) ; 
 TYPE_1__ OSSL_PARAM_ulong (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_mem_eq (unsigned char*,size_t const,unsigned long*,size_t const) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le_copy (unsigned char*,unsigned long*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned long*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* raw_values ; 
 int test_param_type_extra (TYPE_1__*,unsigned long*,int) ; 

__attribute__((used)) static int test_param_ulong(int n)
{
    unsigned long int in, out;
    unsigned char buf[MAX_LEN], cmp[sizeof(unsigned long int)];
    const size_t len = raw_values[n].len >= sizeof(unsigned long int)
                       ? sizeof(unsigned long int) : raw_values[n].len;
    OSSL_PARAM param = OSSL_PARAM_ulong("a", NULL);

    memset(buf, 0, sizeof(buf));
    le_copy(buf, raw_values[n].value, sizeof(in));
    memcpy(&in, buf, sizeof(in));
    param.data = &out;
    if (!TEST_true(OSSL_PARAM_set_ulong(&param, in)))
        return 0;
    le_copy(cmp, &out, sizeof(out));
    if (!TEST_mem_eq(cmp, len, raw_values[n].value, len))
        return 0;
    in = 0;
    if (!TEST_true(OSSL_PARAM_get_ulong(&param, &in)))
        return 0;
    le_copy(cmp, &in, sizeof(in));
    if (!TEST_mem_eq(cmp, sizeof(in), raw_values[n].value, sizeof(in)))
        return 0;
    param.data = &out;
    return test_param_type_extra(&param, raw_values[n].value, sizeof(unsigned long int));
}