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
 void* c_CRYPTO_secure_malloc (size_t,char const*,int) ; 

void *CRYPTO_secure_malloc(size_t num, const char *file, int line)
{
    return c_CRYPTO_secure_malloc(num, file, line);
}