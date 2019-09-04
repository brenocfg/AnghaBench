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
struct TYPE_3__ {int /*<<< orphan*/  (* cb_printf ) (char*,char*) ;} ;
typedef  TYPE_1__ RIO ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* runcmd (char const*) ; 
 int /*<<< orphan*/  stub1 (char*,char*) ; 

__attribute__((used)) static void printcmd (RIO *io, const char *cmd) {
	char *res = runcmd (cmd);
	io->cb_printf ("%s\n", res);
	free (res);
}