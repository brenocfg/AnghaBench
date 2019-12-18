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
typedef  int /*<<< orphan*/  zval ;

/* Variables and functions */
 void* Z_PTR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pefree (void*,int) ; 

__attribute__((used)) static void php_pcre_free_char_table(zval *data)
{/*{{{*/
	void *ptr = Z_PTR_P(data);
	pefree(ptr, 1);
}