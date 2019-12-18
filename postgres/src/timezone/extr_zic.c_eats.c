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
typedef  void* lineno_t ;

/* Variables and functions */
 char const* filename ; 
 void* linenum ; 
 char const* rfilename ; 
 void* rlinenum ; 

__attribute__((used)) static void
eats(char const *name, lineno_t num, char const *rname, lineno_t rnum)
{
	filename = name;
	linenum = num;
	rfilename = rname;
	rlinenum = rnum;
}