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
struct fscache_operation {int /*<<< orphan*/  debug_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fscache_release_write_op(struct fscache_operation *_op)
{
	_enter("{OP%x}", _op->debug_id);
}