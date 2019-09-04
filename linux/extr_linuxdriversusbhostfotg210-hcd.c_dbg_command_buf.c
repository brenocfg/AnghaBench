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
typedef  int u32 ;

/* Variables and functions */
 int CMD_ASE ; 
 int CMD_IAAD ; 
 int CMD_PARK ; 
 int /*<<< orphan*/  CMD_PARK_CNT (int) ; 
 int CMD_PSE ; 
 int CMD_RESET ; 
 int CMD_RUN ; 
 int /*<<< orphan*/ * fls_strings ; 
 int scnprintf (char*,unsigned int,char*,char const*,char*,int,char*,int /*<<< orphan*/ ,int,char*,char*,char*,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int dbg_command_buf(char *buf, unsigned len, const char *label,
		u32 command)
{
	return scnprintf(buf, len,
			"%s%scommand %07x %s=%d ithresh=%d%s%s%s period=%s%s %s",
			label, label[0] ? " " : "", command,
			(command & CMD_PARK) ? " park" : "(park)",
			CMD_PARK_CNT(command),
			(command >> 16) & 0x3f,
			(command & CMD_IAAD) ? " IAAD" : "",
			(command & CMD_ASE) ? " Async" : "",
			(command & CMD_PSE) ? " Periodic" : "",
			fls_strings[(command >> 2) & 0x3],
			(command & CMD_RESET) ? " Reset" : "",
			(command & CMD_RUN) ? "RUN" : "HALT");
}