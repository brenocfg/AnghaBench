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
struct TYPE_3__ {int id; int command; int use_file; } ;
typedef  TYPE_1__ CState ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,char const*,int,char const*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
commandFailed(CState *st, const char *cmd, const char *message)
{
	fprintf(stderr,
			"client %d aborted in command %d (%s) of script %d; %s\n",
			st->id, st->command, cmd, st->use_file, message);
}