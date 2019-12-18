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
#define  NID_aes_128_ctr 130 
#define  NID_aes_192_ctr 129 
#define  NID_aes_256_ctr 128 

__attribute__((used)) static int is_ctr(int type)
{
    switch (type) {
    case NID_aes_128_ctr:
    case NID_aes_192_ctr:
    case NID_aes_256_ctr:
        return 1;
    default:
        return 0;
    }
}