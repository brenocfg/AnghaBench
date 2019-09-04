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

/* Variables and functions */
 int crypto_free_ex_index_ex (int /*<<< orphan*/ *,int,int) ; 

int CRYPTO_free_ex_index(int class_index, int idx)
{
    return crypto_free_ex_index_ex(NULL, class_index, idx);
}