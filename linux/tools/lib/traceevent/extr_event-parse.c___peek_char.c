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
 int* input_buf ; 
 size_t input_buf_ptr ; 
 size_t input_buf_siz ; 

__attribute__((used)) static int __peek_char(void)
{
	if (input_buf_ptr >= input_buf_siz)
		return -1;

	return input_buf[input_buf_ptr];
}