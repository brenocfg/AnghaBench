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
struct srcpos {int dummy; } ;
struct data {int dummy; } ;
struct property {char* name; int /*<<< orphan*/  srcpos; struct data val; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct property*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  srcpos_copy (struct srcpos*) ; 
 struct property* xmalloc (int) ; 

struct property *build_property(char *name, struct data val,
				struct srcpos *srcpos)
{
	struct property *new = xmalloc(sizeof(*new));

	memset(new, 0, sizeof(*new));

	new->name = name;
	new->val = val;
	new->srcpos = srcpos_copy(srcpos);

	return new;
}