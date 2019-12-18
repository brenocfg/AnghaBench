#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ error; } ;
typedef  TYPE_1__ ERR_STRING_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_write_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err_string_lock ; 
 int /*<<< orphan*/  int_error_hash ; 
 int /*<<< orphan*/  lh_ERR_STRING_DATA_insert (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int err_load_strings(const ERR_STRING_DATA *str)
{
    CRYPTO_THREAD_write_lock(err_string_lock);
    for (; str->error; str++)
        (void)lh_ERR_STRING_DATA_insert(int_error_hash,
                                       (ERR_STRING_DATA *)str);
    CRYPTO_THREAD_unlock(err_string_lock);
    return 1;
}