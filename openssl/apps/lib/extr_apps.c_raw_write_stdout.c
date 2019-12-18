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
 int /*<<< orphan*/  fileno_stdout () ; 
 int write (int /*<<< orphan*/ ,void const*,int) ; 

int raw_write_stdout(const void *buf, int siz)
{
    return write(fileno_stdout(), buf, siz);
}