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
typedef  int /*<<< orphan*/  u64 ;
struct symbol {int dummy; } ;
struct dso {int dummy; } ;

/* Variables and functions */
 char* __get_srcline (struct dso*,int /*<<< orphan*/ ,struct symbol*,int,int,int,int /*<<< orphan*/ ) ; 

char *get_srcline(struct dso *dso, u64 addr, struct symbol *sym,
		  bool show_sym, bool show_addr, u64 ip)
{
	return __get_srcline(dso, addr, sym, show_sym, show_addr, false, ip);
}