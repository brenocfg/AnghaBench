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
typedef  int /*<<< orphan*/  strbuffer_t ;

/* Variables and functions */
 int strbuffer_append_bytes (int /*<<< orphan*/ *,char*,int) ; 

int strbuffer_append_byte(strbuffer_t *strbuff, char byte)
{
    return strbuffer_append_bytes(strbuff, &byte, 1);
}