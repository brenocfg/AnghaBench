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
 char const* input_buf ; 
 scalar_t__ input_buf_ptr ; 
 unsigned long long input_buf_siz ; 

__attribute__((used)) static void init_input_buf(const char *buf, unsigned long long size)
{
	input_buf = buf;
	input_buf_siz = size;
	input_buf_ptr = 0;
}