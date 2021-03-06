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
 int /*<<< orphan*/  cipher_table ; 
 int /*<<< orphan*/  engine_table_cleanup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void engine_unregister_all_ciphers(void)
{
    engine_table_cleanup(&cipher_table);
}