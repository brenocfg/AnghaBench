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
 size_t const BUF_SIZE_MAX ; 
 int likely (int) ; 

__attribute__((used)) static inline bool
buf_size_valid(const size_t size)
{
    return likely(size < BUF_SIZE_MAX);
}