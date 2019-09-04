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
typedef  int /*<<< orphan*/  CRYPTO_EX_DATA ;

/* Variables and functions */

__attribute__((used)) static void ui_new_method_data(void *parent, void *ptr, CRYPTO_EX_DATA *ad,
                               int idx, long argl, void *argp)
{
    /*
     * Do nothing, the data is allocated externally and assigned later with
     * CRYPTO_set_ex_data()
     */
}