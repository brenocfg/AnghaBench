#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_bool ;
struct TYPE_3__ {scalar_t__ len; } ;
typedef  TYPE_1__ MYSQLND_READ_BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static zend_bool
mysqlnd_read_buffer_is_empty(const MYSQLND_READ_BUFFER * const buffer)
{
	return buffer->len? FALSE:TRUE;
}