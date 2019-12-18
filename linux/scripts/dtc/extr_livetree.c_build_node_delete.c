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
struct node {int deleted; int /*<<< orphan*/  srcpos; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct node*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  srcpos_copy (struct srcpos*) ; 
 struct node* xmalloc (int) ; 

struct node *build_node_delete(struct srcpos *srcpos)
{
	struct node *new = xmalloc(sizeof(*new));

	memset(new, 0, sizeof(*new));

	new->deleted = 1;
	new->srcpos = srcpos_copy(srcpos);

	return new;
}