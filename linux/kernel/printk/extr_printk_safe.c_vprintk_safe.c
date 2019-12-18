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
typedef  int /*<<< orphan*/  va_list ;
struct printk_safe_seq_buf {int dummy; } ;

/* Variables and functions */
 int printk_safe_log_store (struct printk_safe_seq_buf*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_print_seq ; 
 struct printk_safe_seq_buf* this_cpu_ptr (int /*<<< orphan*/ *) ; 

int vprintk_safe(const char *fmt, va_list args)
{
	struct printk_safe_seq_buf *s = this_cpu_ptr(&safe_print_seq);

	return printk_safe_log_store(s, fmt, args);
}