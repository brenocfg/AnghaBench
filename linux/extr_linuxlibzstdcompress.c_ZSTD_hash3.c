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
typedef  int U32 ;

/* Variables and functions */
 int prime3bytes ; 

__attribute__((used)) static U32 ZSTD_hash3(U32 u, U32 h) { return ((u << (32 - 24)) * prime3bytes) >> (32 - h); }