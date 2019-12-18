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
typedef  int /*<<< orphan*/  ERR_STRING_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_read_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err_string_lock ; 
 int /*<<< orphan*/  int_error_hash ; 
 int /*<<< orphan*/ * lh_ERR_STRING_DATA_retrieve (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static ERR_STRING_DATA *int_err_get_item(const ERR_STRING_DATA *d)
{
    ERR_STRING_DATA *p = NULL;

    CRYPTO_THREAD_read_lock(err_string_lock);
    p = lh_ERR_STRING_DATA_retrieve(int_error_hash, d);
    CRYPTO_THREAD_unlock(err_string_lock);

    return p;
}