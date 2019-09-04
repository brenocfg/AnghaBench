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
typedef  int /*<<< orphan*/  zend_encoding ;

/* Variables and functions */
 int SUCCESS ; 
 int /*<<< orphan*/ ** pemalloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dummy_encoding_list_parser(const char *encoding_list, size_t encoding_list_len, const zend_encoding ***return_list, size_t *return_size, int persistent)
{
	*return_list = pemalloc(0, persistent);
	*return_size = 0;
	return SUCCESS;
}