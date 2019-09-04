#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ SIPHASH ;

/* Variables and functions */
 int SIPHASH_KEY_SIZE ; 
 int SIPHASH_MAX_DIGEST_SIZE ; 
 int /*<<< orphan*/  SipHash_Final (TYPE_1__*,unsigned char*,int) ; 
 int /*<<< orphan*/  SipHash_Init (TYPE_1__*,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SipHash_set_hash_size (TYPE_1__*,int) ; 
 scalar_t__ TEST_int_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_true (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_siphash_basic(void)
{
    SIPHASH siphash = { 0, };
    unsigned char key[SIPHASH_KEY_SIZE];
    unsigned char output[SIPHASH_MAX_DIGEST_SIZE];

    /* Use invalid hash size */
    return TEST_int_eq(SipHash_set_hash_size(&siphash, 4), 0)
           /* Use hash size = 8 */
           && TEST_true(SipHash_set_hash_size(&siphash, 8))
           && TEST_true(SipHash_Init(&siphash, key, 0, 0))
           && TEST_true(SipHash_Final(&siphash, output, 8))
           && TEST_int_eq(SipHash_Final(&siphash, output, 16), 0)

           /* Use hash size = 16 */
           && TEST_true(SipHash_set_hash_size(&siphash, 16))
           && TEST_true(SipHash_Init(&siphash, key, 0, 0))
           && TEST_int_eq(SipHash_Final(&siphash, output, 8), 0)
           && TEST_true(SipHash_Final(&siphash, output, 16))

           /* Use hash size = 0 (default = 16) */
           && TEST_true(SipHash_set_hash_size(&siphash, 0))
           && TEST_true(SipHash_Init(&siphash, key, 0, 0))
           && TEST_int_eq(SipHash_Final(&siphash, output, 8), 0)
           && TEST_true(SipHash_Final(&siphash, output, 16));
}