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
typedef  int /*<<< orphan*/  uint64 ;
typedef  int /*<<< orphan*/  uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  setByteArray (void**,void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void _TIFFsetLong8Array(uint64** lpp, uint64* lp, uint32 n)
    { setByteArray((void**) lpp, (void*) lp, n, sizeof (uint64)); }