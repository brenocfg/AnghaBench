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
 int /*<<< orphan*/  cfb_cipher8 ; 
 int cfb_test (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_des_cfb8(void)
{
    return cfb_test(8, cfb_cipher8);
}