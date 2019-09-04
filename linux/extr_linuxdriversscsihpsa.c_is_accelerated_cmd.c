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
struct CommandList {scalar_t__ cmd_type; } ;

/* Variables and functions */
 scalar_t__ CMD_IOACCEL1 ; 
 scalar_t__ CMD_IOACCEL2 ; 

__attribute__((used)) static int is_accelerated_cmd(struct CommandList *c)
{
	return c->cmd_type == CMD_IOACCEL1 || c->cmd_type == CMD_IOACCEL2;
}