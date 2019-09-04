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
typedef  int /*<<< orphan*/  DSA_METHOD ;

/* Variables and functions */
 int /*<<< orphan*/  const* default_DSA_method ; 

const DSA_METHOD *DSA_get_default_method(void)
{
    return default_DSA_method;
}