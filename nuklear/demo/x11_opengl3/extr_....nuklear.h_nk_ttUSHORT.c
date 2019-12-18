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
typedef  int /*<<< orphan*/  nk_ushort ;
typedef  int nk_byte ;

/* Variables and functions */

__attribute__((used)) static nk_ushort nk_ttUSHORT(const nk_byte *p) { return (nk_ushort)(p[0]*256 + p[1]); }