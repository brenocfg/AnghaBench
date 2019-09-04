#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_hexstr2buf (char const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* RAND_get_rand_method () ; 
 int /*<<< orphan*/  RAND_set_rand_method (TYPE_1__*) ; 
 int /*<<< orphan*/  TEST_ptr (TYPE_1__*) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 TYPE_1__ fake_rand ; 
 int /*<<< orphan*/  fake_rand_bytes ; 
 scalar_t__ fake_rand_bytes_offset ; 
 int fake_rand_size ; 
 int /*<<< orphan*/  get_faked_bytes ; 
 TYPE_1__* saved_rand ; 
 int strlen (char const*) ; 

__attribute__((used)) static int start_fake_rand(const char *hex_bytes)
{
    /* save old rand method */
    if (!TEST_ptr(saved_rand = RAND_get_rand_method()))
        return 0;

    fake_rand = *saved_rand;
    /* use own random function */
    fake_rand.bytes = get_faked_bytes;

    fake_rand_bytes = OPENSSL_hexstr2buf(hex_bytes, NULL);
    fake_rand_bytes_offset = 0;
    fake_rand_size = strlen(hex_bytes) / 2;

    /* set new RAND_METHOD */
    if (!TEST_true(RAND_set_rand_method(&fake_rand)))
        return 0;
    return 1;
}