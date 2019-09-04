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
typedef  int /*<<< orphan*/  SHA512_CTX ;

/* Variables and functions */
 int SHA512_Update (int /*<<< orphan*/ *,void const*,size_t) ; 

int SHA384_Update(SHA512_CTX *c, const void *data, size_t len)
{
    return SHA512_Update(c, data, len);
}