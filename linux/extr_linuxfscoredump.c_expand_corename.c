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
struct core_name {char* corename; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int core_name_size ; 
 char* krealloc (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ksize (char*) ; 

__attribute__((used)) static int expand_corename(struct core_name *cn, int size)
{
	char *corename = krealloc(cn->corename, size, GFP_KERNEL);

	if (!corename)
		return -ENOMEM;

	if (size > core_name_size) /* racy but harmless */
		core_name_size = size;

	cn->size = ksize(corename);
	cn->corename = corename;
	return 0;
}