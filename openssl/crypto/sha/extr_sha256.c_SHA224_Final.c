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
typedef  int /*<<< orphan*/  SHA256_CTX ;

/* Variables and functions */
 int SHA256_Final (unsigned char*,int /*<<< orphan*/ *) ; 

int SHA224_Final(unsigned char *md, SHA256_CTX *c)
{
    return SHA256_Final(md, c);
}