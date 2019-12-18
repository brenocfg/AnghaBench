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
 int AUTHDES_CACHESZ ; 
 short* authdes_lru ; 

__attribute__((used)) static short
cache_victim()
{
	return (authdes_lru[AUTHDES_CACHESZ-1]);
}