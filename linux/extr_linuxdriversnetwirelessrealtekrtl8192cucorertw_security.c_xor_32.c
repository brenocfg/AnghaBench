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
typedef  int u8 ;
typedef  int sint ;

/* Variables and functions */
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 

__attribute__((used)) static void xor_32(u8 *a, u8 *b, u8 *out)
{
    sint i;
_func_enter_;		
    for (i=0;i<4; i++)
    {
        out[i] = a[i] ^ b[i];
    }
_func_exit_;		
}